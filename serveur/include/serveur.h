#ifndef SERVEUR_H
#define SERVEUR_H 1


#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include <QString>
#include <iostream>
#include "serialdata.h"
#include <map>

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
        void sendToAllExceptWeatherStation(Message message);
        void sendToAllComputersExcept(Message message, QTcpSocket* client);
        void sendToAllComputers(Message message);
        void sendToComputer(Message message, int id);
        void sendToAllBoatsExcept(Message message, int id);
        boolean checkConnectionUART(Message msg);
        boolean checkConnectionTCPIP(Message data, QTcpSocket* socket);
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
        void sendIdToUART(int id);
        void treatBoatDatas(Message msg);
        void sendToBoat(Message msg, int id);

        QStringList weatherStationsId;
        QStringList boatsId;
        map<int, int> linkBetweenClientsAndPC;
        map<int, int> linkBetweenPCAndClients;
};


#endif // !SERVEUR_H
