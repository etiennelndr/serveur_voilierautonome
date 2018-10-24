#include "serveur.h"

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
    uart = new SerialData(QString("2929"), nullptr);
    // Connect it -> when receivedDataFromUART signal is emitted, call readDataFromUART slot
    connect(uart, SIGNAL(receivedDataFromUART(Message)), this, SLOT(readDataFromUART(Message)));

    // Set length of message to 0
    tailleMessage = 0;
}

/**
 * DESTRUCTOR
 *
 * @brief ServeurTcp::~ServeurTcp : TODO
 */
ServeurTcp::~ServeurTcp() {
    qDeleteAll(clients);
    delete uart;
    cout << "Server: OFF" << endl;
}

/**
 * SLOT -> this slot is called when newConnection() signal is emitted
 *
 * @brief ServeurTcp::demandeConnexion : TODO
 */
void ServeurTcp::demandeConnexion() {
    envoyerATous(tr("Un client vient de se connecter"));

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
        if (socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
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
    cout << message.toStdString() << endl;

    // On renvoie le message à tous les clients sauf celui qui a envoyé les données
    // ATTENTION: Dans le futur cela ne sera SURTOUT PAS à faire
    envoyerATousSauf(message, socket);

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

    envoyerATousSauf(tr("Un client vient de se déconnecter"), socket);

    clients.removeOne(socket);

    socket->deleteLater();
}

/**
 * METHOD
 *
 * @brief ServeurTcp::envoyerATous : TODO
 * @param message
 */
void ServeurTcp::envoyerATous(const QString &message) {
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;    // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message;        // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - (int)sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message


    // Envoi du paquet préparé à tous les clients connectés au serveur
    for (int i = 0; i < clients.size(); i++) {
        clients[i]->write(paquet);
    }
}

/**
 * METHOD
 *
 * @brief ServeurTcp::envoyerATousSauf : TODO
 * @param message
 * @param client
 */
void ServeurTcp::envoyerATousSauf(const QString &message, QTcpSocket* client) {
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;    // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message;        // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - (int)sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message

    // Envoi du paquet préparé à tous les clients connectés au serveur
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i]->socketDescriptor() != client->socketDescriptor()) {
            clients[i]->write(paquet);
        }
    }
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
 * SLOT -> this slot is called when receivedDataFromUART() signal is emitted
 *
 * @brief ServeurTcp::getDataFromUART : TODO
 * @param msg
 */
void ServeurTcp::readDataFromUART(Message msg) {
    if (msg.getError())
        emit received_data(QString("Error when decoding the message from the UART."));
    else
        emit received_data(msg.encodeData());
}
