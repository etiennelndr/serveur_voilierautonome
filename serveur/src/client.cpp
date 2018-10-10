#include "client.h"

ClientTcp::ClientTcp(QString ip, int port, QString _pseudo) {
	serverPort = port; // choix arbitraire (>1024)
	serverIp = ip;
	pseudo = _pseudo;

	soc = new QTcpSocket(this);

	soc->abort(); // On désactive les connexions précédentes s'il y en a
    soc->connectToHost(serverIp, serverPort); // On se connecte au serveur demandé

	connect(soc, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(soc, SIGNAL(connected()), this, SLOT(connecte()));
    connect(soc, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(soc, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
}

ClientTcp::~ClientTcp() {
	delete soc;
}

void ClientTcp::run() {
    while (true) {
        string msg;
		cout << "Write here: ";
        cin >> msg;
        send(QString::fromStdString(msg));
    }
}

void ClientTcp::send(QString msg) {
	QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // On prépare le paquet à envoyer
    QString messageAEnvoyer = pseudo + " : " + msg;

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    soc->write(paquet); // On envoie le paquet
}

// On a reçu un paquet (ou un sous-paquet)
void ClientTcp::donneesRecues() {
    /* Même principe que lorsque le serveur reçoit un paquet :
    On essaye de récupérer la taille du message
    Une fois qu'on l'a, on attend d'avoir reçu le message entier (en se basant sur la taille annoncée tailleMessage)
    */
    QDataStream in(soc);

    if (tailleMessage == 0) { // Si on ne connaît pas encore la taille du message, on essaye de la récupérer
        if (soc->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas reçu la taille du message en entier
            return;

        in >> tailleMessage; // Si on a reçu la taille du message en entier, on la récupère
    }

	 // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
    if (soc->bytesAvailable() < tailleMessage)
        return; // Si on n'a pas encore tout reçu, on arrête la méthode

    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;

    // On affiche le message sur la zone de Chat
    cout << "\nReceived: " << messageRecu.toStdString() << endl;

    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}

// Ce slot est appelé lorsque la connexion au serveur a réussi
void ClientTcp::connecte() {
    cout << "\nConnexion réussie !" << endl;
}

// Ce slot est appelé lorsqu'on est déconnecté du serveur
void ClientTcp::deconnecte() {
    cout << "\nDéconnecté du serveur" << endl;
}

// Ce slot est appelé lorsqu'il y a une erreur
void ClientTcp::erreurSocket(QAbstractSocket::SocketError erreur) {
    switch(erreur) { // On affiche un message différent selon l'erreur qu'on nous indique
        case QAbstractSocket::HostNotFoundError:
            cout << "\nERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port." << endl;
            break;
        case QAbstractSocket::ConnectionRefusedError:
            cout << "\nERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port." << endl;
            break;
        case QAbstractSocket::RemoteHostClosedError:
            cout << "\nERREUR : le serveur a coupé la connexion." << endl;
            break;
        default:
            cout << "\nERREUR : " << soc->errorString().toStdString() << endl;
    }
}
