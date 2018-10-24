#ifndef SERIALDATA_H
#define SERIALDATA_H 1

#include <QString>
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include "message.h"

/**
 * @brief The SerialData class
 */
class SerialData : public QObject {
    Q_OBJECT
    public:
        SerialData(QString port, QObject *parent=nullptr);
        ~SerialData();

        void sendData(Message msg);

    private:
        // Avoid simple creation of SerialData
        SerialData();

        QSerialPort* mPort;

        QString port;

    private slots:
        void readData();

    signals:
        void receivedDataFromUART(Message);
};

#endif // SERIALDATA_H
