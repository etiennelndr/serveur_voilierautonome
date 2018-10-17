#include "serveur.h"

ServeurTcp::ServeurTcp(quint16 port) {
	if (!(listen(QHostAddress::Any, port))) {
        cout << "Server: OFF" << endl;
    } else {
        cout << "Server: ON" << endl;
        connect(this, SIGNAL(newConnection()), this, SLOT(demandeConnexion()));
    }

    tailleMessage = 0;
}

ServeurTcp::~ServeurTcp() {
    qDeleteAll(clients);
}

void ServeurTcp::demandeConnexion() {
    envoyerATous(tr("Un client vient de se connecter"));

    // On crée une nouvelle socket pour ce client
	QTcpSocket *nouveauClient = nextPendingConnection();
    clients << nouveauClient;

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));
}

void ServeurTcp::donneesRecues() {
    // On reçoit un paquet (ou un sous-paquet) d'un des clients
    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
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

    cout << message.toStdString() << endl;

    // On renvoie le message à tous les clients
    envoyerATousSauf(message, socket);

    // Remise de la taille du message à 0 pour permettre la réception des futurs messages
    tailleMessage = 0;
}

void ServeurTcp::deconnexionClient() {
    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) // Si par hasard on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
        return;

    envoyerATousSauf(tr("Un client vient de se déconnecter"), socket);

    clients.removeOne(socket);

    socket->deleteLater();
}

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

void ServeurTcp::envoyerATousSauf(const QString &message, const QTcpSocket* client) {
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0;    // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message;        // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - (int)sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message


    // Envoi du paquet préparé à tous les clients connectés au serveur
    for (int i = 0; i < clients.size(); i++) {
        if (clients[i] != client) {
            clients[i]->write(paquet);
        }
    }
}
