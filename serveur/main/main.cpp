#include <QApplication>
#include "mainwindow.h"
#include "message.h"

/**
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mw;
    qRegisterMetaType<Message>("Message");
    mw.show();
    return app.exec();
}
