#include <QApplication>
#include "mainwindow.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mw;

    Message msg;
    cout << msg.getError() << endl;
    return 0;

    mw.show();
    return app.exec();
}
