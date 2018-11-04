#include "database.h"

const QString Database::TYPE      = "type";
const QString Database::IDSENDER  = "id_sender";
const QString Database::IDDEST    = "id_dest";
const QString Database::IDCONCERN = "id_concern";
const QString Database::LONGITUDE = "longitude";
const QString Database::LATITUDE  = "latitude";
const QString Database::CAP       = "cap";
const QString Database::VITESSE   = "vitesse";
const QString Database::GITE      = "gite";
const QString Database::TANGAGE   = "tangage";
const QString Database::BARRE     = "barre";
const QString Database::ECOUTE    = "ecoute";

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

/**
 * DESTRUCTOR
 *
 * @brief Database::~Database
 */
Database::~Database() {
    // Close the database
    db.close();
}

/*--------------------------*
 *                          *
 *         METHODS          *
 *                          *
 *--------------------------*/
/**
 * METHOD
 *
 * @brief Database::resetDatabase : reset the database
 * @return
 */
QSqlError Database::resetDatabase() {
    // Initiate a transaction
    db.transaction();

    // Delete all rows
    QSqlQuery query(db);
    // Execute the query
    if (query.exec("DELETE FROM " + dbName))
        db.commit(); // Commit changes
    else
        db.rollback(); // Else rollback changes

    // Return the error (could be empty)
    return query.lastError();
}

/**
 * METHOD
 *
 * @brief Database::insertInDatabase : insert a message in the database
 * @param msg
 * @return
 */
QSqlError Database::insertInDatabase(Message msg) {
    // Initiate a transaction
    db.transaction();

    // Insert in database
    QSqlQuery query(db);
    // Create two QString for the query
    QString columnsName;
    QString values;
    // Transform the message to begin the creation of the query
    transformMessageToQuery(query, msg, columnsName, values);

    // Execute the query
    if (query.exec("INSERT INTO " + dbName + columnsName + values))
        db.commit(); // Commit changes
    else
        db.rollback(); // Else rollback changes

    // Return the error (could be empty)
    return query.lastError();
}

/**
 * METHOD
 *
 * @brief Database::transformMessageToQuery : transform a message to a query
 * @param query
 * @param msg
 * @param columnsName
 * @param values
 */
void Database::transformMessageToQuery(QSqlQuery& query, Message msg, QString& columnsName, QString& values) {
    // Open each one with an open parenthesis
    columnsName.append("(");
    values.append("VALUES (");

    bool isFirst=true;

    if (msg.getType()) {
        addNewValueAndColumnName(columnsName, TYPE, values, isFirst);
        query.addBindValue(QString::fromStdString(*msg.getType()));
    }
    if (msg.getIdSender()) {
        addNewValueAndColumnName(columnsName, IDSENDER, values, isFirst);
        query.addBindValue(*msg.getIdSender());
    }
    if (msg.getIdDest()) {
        addNewValueAndColumnName(columnsName, IDDEST, values, isFirst);
        query.addBindValue(*msg.getIdDest());
    }
    if (msg.getIdConcern()) {
        addNewValueAndColumnName(columnsName, IDCONCERN, values, isFirst);
        query.addBindValue(*msg.getIdConcern());
    }
    if (msg.getLongitude()) {
        addNewValueAndColumnName(columnsName, LONGITUDE, values, isFirst);
        query.addBindValue(*msg.getLongitude());
    }
    if (msg.getLatitude()) {
        addNewValueAndColumnName(columnsName, LATITUDE, values, isFirst);
        query.addBindValue(*msg.getLatitude());
    }
    if (msg.getCap()) {
        addNewValueAndColumnName(columnsName, CAP, values, isFirst);
        query.addBindValue(*msg.getCap());
    }
    if (msg.getVitesse()) {
        addNewValueAndColumnName(columnsName, VITESSE, values, isFirst);
        query.addBindValue(*msg.getVitesse());
    }
    if (msg.getGite()) {
        addNewValueAndColumnName(columnsName, GITE, values, isFirst);
        query.addBindValue(*msg.getGite());
    }
    if (msg.getTangage()) {
        addNewValueAndColumnName(columnsName, TANGAGE, values, isFirst);
        query.addBindValue(*msg.getTangage());
    }
    if (msg.getBarre()) {
        addNewValueAndColumnName(columnsName, BARRE, values, isFirst);
        query.addBindValue(*msg.getBarre());
    }
    if (msg.getEcoute()) {
        addNewValueAndColumnName(columnsName, ECOUTE, values, isFirst);
        query.addBindValue(*msg.getEcoute());
    }

    // Close each one with a close parenthesis
    columnsName.append(")");
    values.append(")");
}

/**
 * METHOD
 *
 * @brief Database::addNewValueAndColumnName : TODO
 * @param columnsName
 * @param values
 * @param isFirst
 */
void Database::addNewValueAndColumnName(QString& columnsName, QString columnName, QString& values, bool& isFirst) {
    if (isFirst) {
        columnsName.append(columnName);
        values.append("?");
        isFirst = false;
    } else {
        columnsName.append(", " + columnName);
        values.append(", ?");
    }
}
