#ifndef DATABASE_H
#define DATABASE_H 1

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <QSqlError>
#include <QVariant>
#include "message.h"

//use the std namespace
using namespace std;

/**
 * @brief The Database class
 */
class Database : public QObject {
    Q_OBJECT
    public:
        Database(QString dbName);
        ~Database();

        // Reset the database
        QSqlError resetDatabase();

        // Inset in the database
        QSqlError insertInDatabase(Message msg);

    private:
        // Qt Database
        QSqlDatabase db;
        // Database name
        QString dbName;

        // State
        bool state;

        // Avoid simple creation of Database
        Database();

        // Database tables
        static const QString ELEMENTS;
        // Columns name of the table Elements
        static const QString TYPE;
        static const QString IDSENDER;
        static const QString IDDEST;
        static const QString IDCONCERN;
        static const QString LONGITUDE;
        static const QString LATITUDE;
        static const QString CAP;
        static const QString VITESSE;
        static const QString GITE;
        static const QString TANGAGE;
        static const QString BARRE;
        static const QString ECOUTE;

        // Transform a message to a query
        void transformMessageToQuery(QSqlQuery &query, Message msg);
        void addNewValueAndColumnName(QString &columnsName, QString columnName, QString& values, bool &isFirst);
        void bindValues(QSqlQuery &query, Message msg);

    signals:
        void isConnected(bool);
};

#endif // DATABASE_H
