#ifndef SERVEUR_H
#define SERVEUR_H 1


#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include <QString>
#include <iostream>
#include <map>
#include "serialdata.h"
#include "message.h"
#include "boat.h"
#include "computer.h"
#include "weatherstation.h"

using namespace std;

/**
 * @brief The ServeurTcp class
 */
class ServeurTcp : public QTcpServer {
    Q_OBJECT
    public:
        ServeurTcp(quint16 port);
        ~ServeurTcp();
        void sendToAllExceptWeatherStation(Message);
        void sendToAllComputersExcept(Message, int);
        void sendToAllComputers(Message);
        void sendToComputer(Message, int);
        void sendToAllBoatsExcept(Message, int);
        boolean checkConnectionUART(Message);
        boolean checkConnectionTCPIP(Message, QTcpSocket*);

    public slots:
		void demandeConnexion();
        void readDataFromTCPIP();
        void deconnexionClient();
        void readDataFromUART(Message);

    signals:
        void received_data(QString);

    private:
        // Each socket represents a client (= a computer)
	    QList<QTcpSocket *> clients;
        quint16             tailleMessage;
        // UART connection for the weathers stations and the boats
        SerialData *uart;

        void sendDataToUART(Message);
        void sendIdToUART(int);
        void treatBoatDatas(Message);
        void sendToBoat(Message, int);

        // ---- WILL BE DELETED IN THE FUTURE ----
        QStringList weatherStationsId;
        QStringList boatsId;
        // ---- WILL BE DELETED IN THE FUTURE ----

        // Boats vector
        vector<Boat>           boats;
        // Computers vector
        vector<Computer>       computers;
        // Weather stations vector
        vector<WeatherStation> weatherStations;

        void addNewBoat(Message);
        void addNewComputer(Message, int);
        void addNewWeatherStation(Message);

        bool isComputerConnected(int);
        bool getComputerWithId(Computer&, int);
        bool getComputerWithIndexOfSocket(Computer&, int);
};


#endif // SERVEUR_H
