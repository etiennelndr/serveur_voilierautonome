#include "client.h"
#include "serveur.h"

#include <QApplication>
//#include <QtConcurrentRun>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    if (argc != 2) {
        cout << "Error: you must start the program this way -> ./serveur [client|serveur]" << endl;
        exit(1);
    }

    if (string(argv[1]) == "serveur") {
        ServeurTcp serveur(4000);
        return app.exec();
    } else if (string(argv[1]) == "client") {
        ClientTcp client(QString("127.0.0.1"), 4000, QString("Etienne"));
        QFuture<void> future = QtConcurrent::run(&client, &ClientTcp::run);
        return app.exec();
    } else {
        cout << "Error: you must start the program this way -> ./serveur [client|serveur]" << endl;
        exit(1);
    }
}
