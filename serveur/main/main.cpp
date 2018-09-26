#include "client.h"
#include "serveur.h"

#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ServeurTcp serveur(4000);

    return app.exec();
}