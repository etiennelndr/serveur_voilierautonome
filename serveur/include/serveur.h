#ifndef SERVEUR_H
#define SERVEUR_H 1


#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include <QString>
#include <iostream>
#include "serialdata.h"

#include "message.h"

using namespace std;

/**
 * @brief The ServeurTcp class
 */
class ServeurTcp : public QTcpServer {
    Q_OBJECT
    public:
        ServeurTcp(quint16 port);
		~ServeurTcp();
        void envoyerATous(const QString &message);
        void envoyerATousSauf(const QString &message, const QTcpSocket* client);
        void envoyerATousSauf(const QString &message, QTcpSocket* client);
//        QString get_message() {return current_message;}


    public slots:
		void demandeConnexion();
        void readDataFromTCPIP();
        void deconnexionClient();
        void readDataFromUART(Message);

    signals:
        void received_data(QString);

    private:
	    QList<QTcpSocket *> clients;
		quint16 tailleMessage;
        SerialData *uart;
//        QString current_message;

        void sendDataToUART(Message msg);
};


#endif // !SERVEUR_H
