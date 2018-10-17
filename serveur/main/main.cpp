#include <QApplication>
#include <QtConcurrentRun>
#include <iostream>
#include <string>

#include "message.h"
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();
    return app.exec();
}
