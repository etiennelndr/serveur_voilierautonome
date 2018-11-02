#ifndef DATABASE_H
#define DATABASE_H 1

#include <QObject>
#include <QSqlDatabase>

/**
 * @brief The Database class
 */
class Database : public QObject {
    Q_OBJECT
    public:
        Database(QString hostName, QString dbName, QString userName, QString password);
        ~Database();

    private:
        // Qt Database
        QSqlDatabase db;
        // Host name
        QString hostName;
        // Database name
        QString dbName;
        // User name
        QString userName;
        // Password
        QString password;

        // State
        bool state;

        Database();

    signals:
        void isConnected(bool);
};

#endif // DATABASE_H
