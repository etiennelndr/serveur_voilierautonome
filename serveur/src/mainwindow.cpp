#include "mainwindow.h"

#include <QMessageBox>
#include "utils.h"

using std::cout;
using std::endl;

/**
 * CONSTRUCTOR
 *
 * @brief MainWindow::MainWindow : Constructor for MainWindow class
 * @param parent
 */
MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->lancement_serveur, SIGNAL(clicked()), this, SLOT(state()));
    connect(ui->button_resetDB, SIGNAL(clicked()), this, SLOT(resetDB()));
    connect(ui->button_exportDatas, SIGNAL(clicked()), this, SLOT(exportDatas()));

    isResettingDatabase = false;
    isExportingDatabase = false;
}

/**
 * DESTRUCTOR
 *
 * @brief MainWindow::~MainWindow : Destructor for MainWindow class
 */
MainWindow::~MainWindow() {
    delete ui;
    delete serveur;
    delete _msg;
}

/*--------------------------*
 *                          *
 *         METHODS          *
 *                          *
 *--------------------------*/
/**
 * METHOD
 *
 * @brief MainWindow::write_in_konsole
 * @param log
 */
void MainWindow::write_in_konsole(QString log) {
    ui->konsole->append(log);
    //cout << log.toStdString() << endl;
}

/*--------------------------*
 *                          *
 *          SLOTS           *
 *                          *
 *--------------------------*/
/**
 * SLOT ->
 *
 * @brief MainWindow::state
 */
void MainWindow::state() {
    if (ui->lancement_serveur->text() == QString("Lancement Serveur") || ui->lancement_serveur->text() == QString("Lancement Serveur + Simulateur UART")) {
        ui->lancement_serveur->setText("Arrêt Serveur");
        serveur = new ServeurTcp (4000, ui->COM->value());
        ui->COM->close();
        ui->label_uart->close();
        ui->widget_uart->close();
        connect(serveur, SIGNAL(received_data(QString)), this, SLOT(msg_processing(QString)));
        connect(ui->UARTsimulator, SIGNAL(clicked()), this, SLOT(start_uart()));
    } else if (ui->lancement_serveur->text() == QString("Arrêt Serveur")) {
        ui->lancement_serveur->setText("Lancement Serveur");
        delete serveur;
        serveur = nullptr;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::start_uart : TODO
 */
void MainWindow::start_uart() {
    if (serveur) {
        serveur->start_uart();
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::exportDatas : TODO
 */
void MainWindow::exportDatas() {
    if (!serveur) {
        isExportingDatabase = true;

        cout << "exportDatas" << endl;
        serveur = new ServeurTcp();

        // Retrieve the id of the spin box
        int id = ui->spinBox_exportDatas->value();

        QString result = serveur->exportDatas(id);

        if (result == "Unknown error")
            QMessageBox::information(this, "Succès", "L'exportation des données a été exécutée avec succès");
        else
            QMessageBox::information(this, "Erreur", result);

        // Close the server
        delete serveur;
        serveur = nullptr;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::resetDB : TODO
 */
void MainWindow::resetDB() {
    if (!serveur) {
        // Inform the user that the database is going to be reset -> ask for approval
        QMessageBox msgBox;
        msgBox.setText("Vous vous apprêtez à réinitialiser la base de données.");
        msgBox.setInformativeText("Êtes-vous sûr de vouloir effectuer cette action ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        switch (msgBox.exec()) {
            case QMessageBox::Yes:
                isResettingDatabase = true;

                serveur = new ServeurTcp();

                // Reset the database
                QSqlError err = serveur->resetDb();
                if (err.type() == QSqlError::NoError)
                    QMessageBox::information(this, "Succès", "La base de données a été réinitialisée avec succès");
                else
                    QMessageBox::information(this, "Erreur", err.text());

                // Close the server
                delete serveur;
                serveur = nullptr;
                break;
        }
    }
}

/**
 * SLOT -> this slot is called when received_data() signal is emitted
 *
 * @brief MainWindow::msg_processing : TODO
 * @param msg
 */
void MainWindow::msg_processing(QString msg){
    write_in_konsole(msg);
}
