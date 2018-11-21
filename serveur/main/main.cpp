#include <QApplication>
#include "mainwindow.h"
#include "message.h"

#include "utils.h"


using namespace std;


/**
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char* argv[]) {
    /*
    QApplication app(argc, argv);
    MainWindow mw;
    qRegisterMetaType<Message>("Message");
    mw.show();
    return app.exec();
    */
    cout << exePath() << endl;

    // Connect to the database
    Database db(QString("C:\\Users\\Etienne\\Documents\\GitHub\\serveur_voilierautonome\\serveur\\voilierautonome.db"));
    QSqlError err = db.resetDatabase();
    if (err.type() != QSqlError::NoError)
        cout << "Erreur: " << err.text().toStdString() << endl;

    Message msg;
    string m = "__128&type:S&id_dest:1&id_sender:0&id_concern:1&128//";
    msg.decodeData(QString::fromStdString(m));

    QSqlError error = db.insertInDatabase(msg);
    //if (err.type() != QSqlError::NoError)
        cout << "Erreur: " << err.text().toStdString() << endl;

    return 0;
}
