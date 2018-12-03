#include "serveur.h"

#include "utils.h"

using std::cout;
using std::endl;

/**
 * CONSTRUCTOR
 *
 * @brief ServeurTcp::ServeurTcp : default constructor
 */
ServeurTcp::ServeurTcp() {

}

/**
 * CONSTRUCTOR
 *
 * @brief ServeurTcp::ServeurTcp : TODO
 * @param port
 */
ServeurTcp::ServeurTcp(quint16 port) {
    // Open the connection
	if (!(listen(QHostAddress::Any, port))) {
        cout << "Server: OFF" << endl;
    } else {
        cout << "Server: ON" << endl;
        connect(this, SIGNAL(newConnection()), this, SLOT(demandeConnexion()));
    }

    // Create the UART
    uart = new SerialData(QString("COM5"), nullptr);
    // Connect it -> when receivedDataFromUART signal is emitted, call readDataFromUART slot
    connect(uart, SIGNAL(receivedDataFromUART(Message)), this, SLOT(readDataFromUART(Message)));

    // Connect to the database
    db = new Database(QString::fromStdString(exePath() + "\\..\\..\\serveur\\voilierautonome.db"));

    // Set length of message to 0
    tailleMessage = 0;
}

/**
 * DESTRUCTOR
 *
 * @brief ServeurTcp::~ServeurTcp : TODO
 */
ServeurTcp::~ServeurTcp() {
    if (isListening()) {
        qDeleteAll(clients);
        delete uart;
        delete db;
    }
    cout << "Server: OFF" << endl;
}

/*--------------------------*
 *                          *
 *         METHODS          *
 *                          *
 *--------------------------*/
/**
 * METHOD
 *
 * @brief ServeurTcp::start_uart : start the uart simulator on the Arduino
 * @param message
 */
void ServeurTcp::start_uart(){
    uart->start_simulator();
}

/**
 * METHOD
 *
 * @brief ServeurTcp::sendToAll : send to all TCP/IP clients (members of computers vector)
 * @param message
 */
void ServeurTcp::sendToAll(Message message, bool _computers=false, bool _boats=false, bool _weatherStations=false, int id_boat_exception=0, int id_computer_exception=0) {
    cout << "sendToAll" << endl;

    message.setType(new string("S"));
    message.setIdSender(new int(0));
    if(_computers) { //send to computers
        // Envoi du paquet préparé à tous les clients connectés au serveur
        for (unsigned int i = 0; i < computers.size(); i++) {
            if (computers.at(i).getId() != id_computer_exception) {
                message.setIdDest(new int(computers.at(i).getId()));
                sendDataToTCP(message.copy(), computers.at(i).getIndexOfSocket());
            }
        }
    }
    if(_boats) { //send to boats
        for (unsigned int i=0; i < boats.size(); i++) {
            if (boats.at(i).get_id() != id_boat_exception) {
                message.setIdDest(new int(boats.at(i).get_id()));
                sendDataToUART(message.copy());
            }
        }
    }
    if(_weatherStations) { //send to weather stations
        for (unsigned int i=0; i < weatherStations.size(); i++) {
            message.setIdDest(new int((boats.at(i).get_id())));
            sendDataToUART(message.copy());
        }
    }
}

/**
 * METHOD
 *
 * @brief ServeurTcp::sendToComputer : send a message to one and only one client
 * @param message
 * @param client
 */
void ServeurTcp::sendToComputer(Message message, int id) {
    cout << "sendToComputer" << endl;
    // Préparation du paquet
    message.setType(new string("S"));
    message.setIdSender(new int(0));
    message.setIdDest(new int(id));
    Computer c;
    if (getComputerWithId(c, id))
        sendDataToTCP(message,c.getIndexOfSocket());
}

/**
 * METHOD
 *
 * @brief ServeurTcp::sendToBoat: TODO
 * @param msg
 * @param id
 */
void ServeurTcp::sendToBoat(Message msg, int id) {
    msg.setType(new string("S"));
    msg.setIdConcern(new int (id));
    msg.setIdDest(new int(id));
    msg.setIdSender(new int(0));
    sendDataToUART(msg);
}

/**
 * METHOD
 *
 * @brief ServeurTcp::sendDataToUART : send data to the UART
 * @param msg
 */
void ServeurTcp::sendDataToUART(Message msg) {
    uart->sendData(msg);
}

/**
 * METHOD
 *
 * @brief ServeurTcp::checkConnectionUART : TODO
 * @param msg
 * @return bool
 */
bool ServeurTcp::checkConnectionUART(Message msg) {
    if (msg.getType()->length() != 2)
        return false;

    cout << msg.encodeData().toStdString() << endl;

    if (*msg.getType() == "MC") {
        // Connection d'une station météo
        addNewWeatherStation(msg);
        Message* message = new Message();
        message->setIdConcern(msg.copy().getIdConcern()); //Signaler a tous les postes la connexion d'une nouvelle station meteo
        sendToAll(message->copy(),true);
    } else if (*msg.getType() == "BC") {
        // Connection d'un bateau
        addNewBoat(msg);
        Message* message = new Message();
        message->setIdConcern(msg.copy().getIdConcern()); //Signaler a tous les postes la connexion d'un nouveau bateau
        sendToAll(message->copy(),true);
    }

    return true;
}

/**
 * METHOD
 *
 * @brief ServeurTcp::sendDataToTCP : send data to the TCP
 * @param msg
 * @param id_socket
 */
void ServeurTcp::sendDataToTCP(Message msg, int id_socket) {
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << quint16(0);    // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << msg.encodeData();        // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << quint16((paquet.size() - int(sizeof(quint16)))); // On écrase le 0 qu'on avait réservé par la longueur du message
    clients[id_socket]->write(paquet);
}

/**
 * METHOD
 *
 * @brief ServeurTcp::checkConnectionTCPIP : TODO
 * @param data
 * @param socket
 */
bool ServeurTcp::checkConnectionTCPIP(Message data, QTcpSocket* socket) {
    if (data.getType()->length() != 2)
        return false;

    int index = clients.indexOf(socket);
    addNewComputer(data.copy(), index);

    cout << "Nouveau client :" << *data.getIdSender() << endl;

    Message* msg = new Message();
    msg->setType(new string("S"));
    msg->setIdSender(new int(0));
    for (unsigned int i=0; i<boats.size();i++){ //Envoyer au nouveau client les bateaux deja enregistres
        msg->setIdConcern(new int(boats.at(i).get_id()));
        sendToComputer(msg->copy(), *data.getIdConcern());
    }
    for (unsigned int i=0; i<weatherStations.size();i++){ //Envoyer au nouveau client les stations meteo deja enregistres
        msg->setIdConcern(new int(weatherStations.at(i).get_id()));
        sendToComputer(msg->copy(), *data.getIdConcern());
    }

    return true;
}

/**
 * METHOD
 *
 * @brief ServeurTcp::treatTCPIPMessage : TODO
 * @param msg
 */
void ServeurTcp::treatBoatDatas(Message msg) {
    // Insert datas in the database
    QSqlError err = db->insertInDatabase(msg.copy());
    if (err.type() != QSqlError::NoError)
        cout << "Erreur: " << err.text().toStdString() << endl;

    // TODO
}

/**
 * METHOD
 *
 * @brief ServeurTcp::getComputer : TODO
 * @param c
 * @param id
 * @return bool
 */
bool ServeurTcp::getComputerWithId(Computer &c, int id) {
    for (unsigned int i=0; i<computers.size(); i++) {
        if (computers[i].getId() == id) {
            c = computers[i];
            return true;
        }
    }
    return false;
}

/**
 * METHOD
 *
 * @brief ServeurTcp::getComputerWithIndexOfSocket : TODO
 * @param c
 * @param indexOfSocket
 * @return bool
 */
bool ServeurTcp::getComputerWithIndexOfSocket(Computer &c, int indexOfSocket) {
    for (unsigned int i=0; i<computers.size(); i++) {
        if (computers[i].getIndexOfSocket() == indexOfSocket) {
            c = computers[i];
            return true;
        }
    }
    return false;
}

/**
 * METHOD
 *
 * @brief ServeurTcp::addNewBoat : add a new boat to the boats vector
 * @param b
 */
void ServeurTcp::addNewBoat(Message b) {
    Boat boat(*b.getIdConcern());

    bool isInBoatsVector = false;
    for (unsigned int i=0; i < boats.size(); i++) {
        if (boats[i].get_id() == *b.getIdConcern()) {
            isInBoatsVector = true;
            break;
        }
    }

    if (!isInBoatsVector) {
        // Push it in the vector boats
        boats.push_back(boat);
        qDebug() << "New boat with id : " << *b.getIdConcern();
    } else
        qDebug() << "Boat with id " << *b.getIdConcern() << " is already registered.";
}

/**
 * METHOD
 *
 * @brief ServeurTcp::addNewComputer : add a new computer to the computers vector
 * @param c
 * @param indexOfSocket
 */
void ServeurTcp::addNewComputer(Message c, int indexOfSocket) {
    Computer computer(*c.getIdConcern(), indexOfSocket);

    bool isInComputersVector = false;
    for (unsigned int i=0; i < computers.size(); i++) {
        if (computers[i].getId() == *c.getIdConcern()) {
            isInComputersVector = true;
            break;
        }
    }

    if (!isInComputersVector) {
        // Push it in the vector computers
        computers.push_back(computer);
        qDebug() << "New computer with id : " << *c.getIdConcern();
    } else
        qDebug() << "Computer with id " << *c.getIdConcern() << " is already registered.";
}

/**
 * METHOD
 *
 * @brief ServeurTcp::addNewWeatherStation : add a new weatherStation to the weatherStations vector
 * @param ws
 */
void ServeurTcp::addNewWeatherStation(Message ws) {
    WeatherStation weatherStation(*ws.getIdConcern());

    bool isInWeatherStationsVector = false;
    for (unsigned int i=0; i < weatherStations.size(); i++) {
        if (weatherStations[i].get_id() == *ws.getIdConcern()) {
            isInWeatherStationsVector = true;
            break;
        }
    }

    if (!isInWeatherStationsVector) {
        // Push it in the vector weatherStations
        weatherStations.push_back(weatherStation);
        qDebug() << "New weatherstation with id : " << *ws.getIdConcern();
    } else
        qDebug() << "Weather station with id " << *ws.getIdConcern() << " is already registered.";
}


/**
 * METHOD
 *
 * @brief ServeurTcp::transferDataFromUARTToComputersAndBoats : TODO
 * @param msg
 */
void ServeurTcp::transferDataFromUARTToComputersAndBoats(Message msg){
    // Transmit datas to computer
    if (*msg.getIdSender() > 0) {
        // This message comes from a boat
        // First of all, treat the datas
        treatBoatDatas(msg.copy());
        Message msg_for_all;
        // Send all datas to the computer which is linked to the boat
        sendToComputer(msg.copy(), *msg.getIdConcern());
        // Send longitude and latitude to other boats and computers
        if(filterMessageFromBoat(msg.copy(), &msg_for_all)) {
            sendToAll(msg_for_all, true, true, false, *msg.getIdConcern(), *msg.getIdConcern());
        }
    } else if (*msg.getIdConcern() < 0) {
        // This message comes from a weather station
        sendToAll(msg.copy(), true, true, false); //Send to all boats and computers
    }
}

/**
 * METHOD
 *
 * @brief ServeurTcp::filterMessageFromBoat : Selections of data to be transfered to all computers and boats
 * @param original
 * @param for_all
 * @return bool
 */
bool ServeurTcp::filterMessageFromBoat(Message original, Message* for_all){
    cout << "filterMessageFromBoat" << endl;
    bool result=false;
    if(original.getLongitude()) {
        for_all->setLongitude(original.getLongitude());
        result=true;
    }

    if(original.getLatitude()) {
        for_all->setLatitude(original.getLatitude());
        result=true;
    }

    if(original.getCap()) {
        for_all->setCap(original.getCap());
        result=true;
    }

    if(result) {
        for_all->setType(original.getType());
        for_all->setIdSender(original.getIdSender());
        for_all->setIdDest(original.getIdDest());
        for_all->setIdConcern(original.getIdConcern());
    }
    return result;
}



/*--------------------------*
 *                          *
 *          SLOTS           *
 *                          *
 *--------------------------*/
/**
 * SLOT -> this slot is called when newConnection() signal is emitted
 *
 * @brief ServeurTcp::demandeConnexion : TODO
 */
void ServeurTcp::demandeConnexion() {
    // On crée une nouvelle socket pour ce client
    QTcpSocket *nouveauClient = nextPendingConnection();
    clients << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(readDataFromTCPIP()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}

/**
 * SLOT -> this slot is called when readyRead() signal is emitted
 *
 * @brief ServeurTcp::donneesRecues : TODO
 */
void ServeurTcp::readDataFromTCPIP() {
    // On reçoit un paquet (ou un sous-paquet) d'un des clients
    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    // Si tout va bien, on continue : on récupère le message
    QDataStream in(socket);

    if (tailleMessage == 0) { // Si on ne connaît pas encore la taille du message, on essaye de la récupérer
        if (socket->bytesAvailable() < int(sizeof(quint16))) // On n'a pas reçu la taille du message en entier
            return;

        in >> tailleMessage; // Si on a reçu la taille du message en entier, on la récupère
    }

    // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (socket->bytesAvailable() < tailleMessage) // Si on n'a pas encore tout reçu, on arrête la méthode
        return;

    // Si ces lignes s'exécutent, c'est qu'on a reçu tout le message : on peut le récupérer.
    QString message;
    in >> message;

    emit received_data(message);

    Message data;
    data.decodeData(message);
    // Verify if an error occured during the decoding
    if (!data.getError()) {
        // Check if it's the first connection
        if (!checkConnectionTCPIP(data.copy(), socket)) {
            // If not we must send the datas to the boat
            sendToBoat(data.copy(), *data.getIdSender());
        }
    }

    // Remise de la taille du message à 0 pour permettre la réception des futurs messages
    tailleMessage = 0;
}

/**
 * SLOT -> this slot is called when disconnected() signal is emitted
 *
 * @brief ServeurTcp::deconnexionClient : TODO
 */
void ServeurTcp::deconnexionClient() {
    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    int index = clients.indexOf(socket);
    for (unsigned int i=0; i<computers.size(); i++) {
        if (computers[i].getIndexOfSocket() == index)
            computers.erase(computers.begin() + int(i));
    }
    clients.removeOne(socket);

    socket->deleteLater();
}

/**
 * SLOT -> this slot is called when receivedDataFromUART() signal is emitted
 *
 * @brief ServeurTcp::getDataFromUART : TODO
 * @param msg
 */
void ServeurTcp::readDataFromUART(Message msg) {
    if (msg.getError()){
        emit received_data(QString("Error when decoding the message from the UART."));
    }
    else {
        emit received_data(msg.encodeData());

        if (!msg.getError() && !checkConnectionUART(msg.copy())) {
            transferDataFromUARTToComputersAndBoats(msg.copy());
        }
    }
}
