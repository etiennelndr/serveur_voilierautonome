#ifndef MOC_UART_H
#define MOC_UART_H 1

#include <QThread>

class ServeurTcp;

class UARTThread : public QThread {
    Q_OBJECT

    public:
        UARTThread(ServeurTcp* s);

        void stop();

    protected:
        void run();

    private:
        ServeurTcp * serveur;

        bool isRunning;
};

#endif // MOC_UART_H
