#include "mocUart.h"
#include "serveur.h"

UARTThread::UARTThread(ServeurTcp* s) {
    this->serveur = s;
    this->isRunning = true;
}

void UARTThread::stop() {
    this->isRunning = false;
    exit();
}

void UARTThread::run() {
    //QThread::sleep(5);
    for(int i=0; (i < 100) && this->isRunning; i++) {
        cout << "yolo" << endl;
        Message msg;
        msg.setType(new string("S"));
        msg.setIdSender(new int(0));
        msg.setIdConcern(new int(1));
        msg.setIdDest(new int(1));
        msg.setLongitude(new float(-4.486076f));
        msg.setLatitude(new float(48.390394f));
        // Emit a signal so that the server knows we "received" a new message from the UART
        serveur->readDataFromUART(msg);
        // Wait a little buddy
        cout << i << endl;
        QThread::sleep(1);
    }
}


