#include "mainwindow.h"

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
 * @brief MainWindow::exportDatasOf : TODO
 */
void MainWindow::exportDatas() {
    if (!serveur) {
        cout << "exportDatas" << endl;
    }
}

/**
 * SLOT -> TODO
 *
 * @brief MainWindow::resetDB : TODO
 */
void MainWindow::resetDB() {
    cout << "resetDB" << endl;
    /*
    Database db(QString::fromStdString(exePath() + "\\..\\..\\serveur\\voilierautonome.db"));
    QSqlError err = db.resetDatabase();
    if (err.type() != QSqlError::NoError)
        cout << "Erreur: " << err.text().toStdString() << endl;*/
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
