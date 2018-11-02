#include "database.h"

/**
 * CONSTRUCTOR
 *
 * @brief Database::Database
 */
Database::Database(QString hostName, QString dbName, QString userName, QString password) :
    hostName(hostName),
    dbName(dbName),
    userName(userName),
    password(password) {
    // Create the database using MySQL SGBDR
    db = QSqlDatabase::addDatabase("QMYSQL");
    // Set the host name
    db.setHostName(this->hostName);
    // Set the database name
    db.setDatabaseName(this->dbName);
    // Set the user name
    db.setUserName(this->userName);
    // Set the password
    db.setPassword(this->password);
    // Open the  database and emit its returned value
    state = db.open();
    emit isConnected(state);
}

Database::~Database() {
    // Close the database
    db.close();
}
