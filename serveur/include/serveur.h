#ifndef SERVEUR_H
#define SERVEUR_H 1


#include <QObject>
#include <QtGui>
#include <QtNetwork>
#include <QString>
#include <QDebug>
#include <iostream>
#include <map>
#include "serialdata.h"
#include "message.h"
#include "boat.h"
#include "computer.h"
#include "weatherstation.h"
#include "database.h"

using std::string;

/**
 * @brief The ServeurTcp class
 */
class ServeurTcp : public QTcpServer {
    Q_OBJECT
    public:
        ServeurTcp(quint16 port, int uart_port);
        ServeurTcp();
        ~ServeurTcp();
        void start_uart();

        // Resetting the database
        QSqlError resetDb();
        // Exporting datas
        QString exportDatas(int);

        Database* getDb();

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
        SerialData *uart = nullptr;

        void sendDataToUART(Message);
        void sendDataToTCP(Message msg, int id_client);
        void sendIdToUART(int);
        void treatBoatDatas(Message);
        void sendToBoat(Message, int);
        void transferDataFromUARTToComputersAndBoats(Message msg);
        bool filterMessageFromBoat(Message original, Message* for_all);

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

        void sendToAll(Message message, bool _computers, bool _boats, bool _weatherStations, int id_boat_exception, int id_computer_exception);
        void sendToAllExceptWeatherStation(Message);
        void sendToAllComputersExcept(Message, int);
        void sendToAllComputers(Message);
        void sendToComputer(Message, int);
        void sendToAllBoatsExcept(Message, int);
        bool checkConnectionUART(Message);
        bool checkConnectionTCPIP(Message, QTcpSocket*);

        // Database to store each message
        Database* db = nullptr;
};

inline Database* ServeurTcp::getDb() { return this->db; }


#endif // SERVEUR_H
