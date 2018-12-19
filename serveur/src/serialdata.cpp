#include "serialdata.h"

#include "utils.h"

using std::cout;

/**
 * CONSTRUCTOR
 *
 * @brief SerialData::SerialData : TODO
 * @param port
 * @param parent
 */
SerialData::SerialData(QString port, QObject *parent) : QObject(parent) {
    mPort = new QSerialPort(this);
    connect(mPort, SIGNAL(readyRead()), this, SLOT(readData()));

    mPort->setPortName(QString(port));
    mPort->setBaudRate(QSerialPort::Baud9600);
    mPort->setDataBits(QSerialPort::Data8);
    mPort->setParity(QSerialPort::NoParity);
    mPort->setStopBits(QSerialPort::OneStop);
    mPort->setFlowControl(QSerialPort::NoFlowControl);

    if(mPort->open(QIODevice::ReadWrite)) {
        mPort->setTextModeEnabled(true);
        qDebug() << "Port open at " << mPort->portName();
        mPort->clear();
        start_simulator();
    } else {
        qDebug() << "Failed to open port " << mPort->portName();
    }
}

/**
 * DESTRUCTOR
 *
 * @brief SerialData::~SerialData : TODO
 */
SerialData::~SerialData() {
    mPort->close();
    delete mPort;
}

/*--------------------------*
 *                          *
 *         METHODS          *
 *                          *
 *--------------------------*/
/**
 * METHOD
 *
 * @brief SerialData::sendData : send data to the UART
 * @param msg
 */
void SerialData::sendData(Message msg) {
    // Encode the data
    QString data = msg.encodeData();
    // Send it to the UART
    mPort->write(data.toStdString().c_str(), data.length());
}

void SerialData::start_simulator() {
    mPort->write("r");
}

/*--------------------------*
 *                          *
 *          SLOTS           *
 *                          *
 *--------------------------*/
/**
 * SLOT -> this slot is called when readyRead() signal is emitted
 *
 * @brief SerialData::readData : read data from UART
 */
void SerialData::readData() {
    QString datas = QString(mPort->readAll().data());
    //qDebug() << "Serial data IN : " << datas;

    // Split datas because we can receive multiple messages in a single row
    vector<string> messages = split(datas.toStdString(), "//");
    for (unsigned int i=0; i<messages.size(); i++) {
        // Add end marker
        messages[i] += "//";
        // Decode data
        Message msg;
        if(QString::fromStdString(messages[i]).length()>4){
            msg.decodeData(QString::fromStdString(messages[i]));
            // Emit a signal to inform the server we received
            // datas from the UART
            emit receivedDataFromUART(msg.copy());
        }
    }
}
