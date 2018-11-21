#include "database.h"

const QString Database::ELEMENTS  = "elements";
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

#include <iostream>

/**
 * CONSTRUCTOR
 *
 * @brief Database::Database
 */
Database::Database(QString dbName) : dbName(dbName) {
    // Create the database using SQLite SGBDR
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(this->dbName);
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
    // Remove the database to avoid "duplicate connection name" warning
    QSqlDatabase::removeDatabase("QSQLITE");
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
    if (query.exec("DELETE FROM " + ELEMENTS))
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
    // Transform the message to begin the creation of the query
    transformMessageToQuery(query, msg.copy());

    // Bind values
    bindValues(query, msg.copy());

    // Execute the query
    if (query.exec())
        db.commit(); // Commit changes
    else
        db.rollback(); // Else rollback changes

    // Return the error (could be empty)
    return query.lastError();
}

/**
 * METHOD
 *
 * @brief Database::bindValues : TODO
 * @param query
 * @param msg
 */
void Database::bindValues(QSqlQuery &query, Message msg) {
    if (msg.getType()) {
        query.bindValue(":"+TYPE, QString::fromStdString(*msg.getType()));
    }
    if (msg.getIdSender()) {
        query.bindValue(":"+IDSENDER, *msg.getIdSender());
    }
    if (msg.getIdDest()) {
        query.bindValue(":"+IDDEST, *msg.getIdDest());
    }
    if (msg.getIdConcern()) {
        query.bindValue(":"+IDCONCERN, *msg.getIdConcern());
    }
    if (msg.getLongitude()) {
        query.bindValue(":"+LONGITUDE, *msg.getLongitude());
    }
    if (msg.getLatitude()) {
        query.bindValue(":"+LATITUDE, *msg.getLatitude());
    }
    if (msg.getCap()) {
        query.bindValue(":"+CAP, *msg.getCap());
    }
    if (msg.getVitesse()) {
        query.bindValue(":"+VITESSE, *msg.getVitesse());
    }
    if (msg.getGite()) {
        query.bindValue(":"+GITE, *msg.getGite());
    }
    if (msg.getTangage()) {
        query.bindValue(":"+TANGAGE, *msg.getTangage());
    }
    if (msg.getBarre()) {
        query.bindValue(":"+BARRE, *msg.getBarre());
    }
    if (msg.getEcoute()) {
        query.bindValue(":"+ECOUTE, *msg.getEcoute());
    }
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
void Database::transformMessageToQuery(QSqlQuery& query, Message msg) {
    // Create two QString for the query
    QString columnsName;
    QString values;

    // Open each one with an open parenthesis
    columnsName.append("(");
    values.append("VALUES (");

    bool isFirst=true;

    if (msg.getType()) {
        addNewValueAndColumnName(columnsName, TYPE, values, isFirst);
    }
    if (msg.getIdSender()) {
        addNewValueAndColumnName(columnsName, IDSENDER, values, isFirst);
    }
    if (msg.getIdDest()) {
        addNewValueAndColumnName(columnsName, IDDEST, values, isFirst);
    }
    if (msg.getIdConcern()) {
        addNewValueAndColumnName(columnsName, IDCONCERN, values, isFirst);
    }
    if (msg.getLongitude()) {
        addNewValueAndColumnName(columnsName, LONGITUDE, values, isFirst);
    }
    if (msg.getLatitude()) {
        addNewValueAndColumnName(columnsName, LATITUDE, values, isFirst);
    }
    if (msg.getCap()) {
        addNewValueAndColumnName(columnsName, CAP, values, isFirst);
    }
    if (msg.getVitesse()) {
        addNewValueAndColumnName(columnsName, VITESSE, values, isFirst);
    }
    if (msg.getGite()) {
        addNewValueAndColumnName(columnsName, GITE, values, isFirst);
    }
    if (msg.getTangage()) {
        addNewValueAndColumnName(columnsName, TANGAGE, values, isFirst);
    }
    if (msg.getBarre()) {
        addNewValueAndColumnName(columnsName, BARRE, values, isFirst);
    }
    if (msg.getEcoute()) {
        addNewValueAndColumnName(columnsName, ECOUTE, values, isFirst);
    }

    // Close each one with a close parenthesis
    columnsName.append(")");
    values.append(")");

    // Prepare the query
    query.prepare("INSERT INTO " + ELEMENTS + " " + columnsName + " " + values);
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
        values.append(":"+columnName);
        isFirst = false;
    } else {
        columnsName.append(", " + columnName);
        values.append(", :"+columnName);
    }
}
