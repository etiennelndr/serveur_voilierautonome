#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QtNetwork>
#include <QString>
#include <iostream>

using namespace std;

class ClientTcp : public QObject {
    Q_OBJECT
    public: 
	    ClientTcp(QString ip, int port=4000);
        ~ClientTcp();
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
};


#endif // !CLIENT_H