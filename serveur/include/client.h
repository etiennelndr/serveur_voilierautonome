#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QtNetwork>
#include <QString>
#include <iostream>
#include <unistd.h>

using namespace std;

class ClientTcp : public QObject {
    Q_OBJECT
    public: 
	    ClientTcp(QString ip, int port, QString _pseudo);
        ~ClientTcp();
        void run();
    private slots:
        void donneesRecues();
        void connecte();
        void deconnecte();
        void erreurSocket(QAbstractSocket::SocketError erreur);
    private:
        // Ip du serveur
	    QString serverIp;
        // Port utilisé par le serveur
	    int serverPort;
        // Socket
	    QTcpSocket* soc;
        // Taille du message
        quint16 tailleMessage;
        // Pseudo de l'utilisateur
        QString pseudo;

        // Method to send a message to the server
        void send(QString msg);
};


#endif // !CLIENT_H
