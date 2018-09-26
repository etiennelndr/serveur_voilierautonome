#ifndef CLIENT_H
#define CLIENT_H


#include <QObject>
#include <QtNetwork>
#include <QString>

class ClientTcp : public QObject {
    Q_OBJECT
    public : 
	    ClientTcp(QString ip);
		void connectToServer();
	    void run();
    private :
        // Ip du serveur
	    QString serverIp;
        // Port utilisé par le serveur
	    int serverPort;
        // Socket
	    QTcpSocket soc;
};


#endif // !CLIENT_H