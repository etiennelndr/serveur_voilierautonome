#ifndef SERIALDATA_H
#define SERIALDATA_H 1

#include <QString>
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include "message.h"

class SerialData : public QObject {
    Q_OBJECT
    public:
        SerialData(QString port, QObject *parent=nullptr);
        ~SerialData();

    private:
        // Avoid simple creation of SerialData
        SerialData();

        QSerialPort* mPort;

        QString port;

        Message* msg;

    private slots:
        void readData();
        void sendData(Message msg);

    signals:
        void receivedDataFromUART(Message);
};

#endif // SERIALDATA_H
