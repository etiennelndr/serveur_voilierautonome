#include "mainwindow.h"

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
    //ui->konsole->append(log);
    cout << log.toStdString() << endl;
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
    if (ui->lancement_serveur->text() == QString("Lancement Serveur")) {
        ui->lancement_serveur->setText("Arrêt Serveur");
        serveur = new ServeurTcp (4000);
        connect(serveur, SIGNAL(received_data(QString)), this, SLOT(msg_processing(QString)));
        connect(ui->UARTsimulator, SIGNAL(clicked()), this, SLOT(start_uart()));
    } else if (ui->lancement_serveur->text() == QString("Arrêt Serveur")) {
        ui->lancement_serveur->setText("Lancement Serveur");
        delete serveur;
        serveur = nullptr;
    }
}

/**
 * SLOT ->
 *
 * @brief MainWindow::start_uart : TODO
 */
void MainWindow::start_uart() {
    if (serveur) {
        serveur->start_uart();
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
