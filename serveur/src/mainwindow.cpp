#include "mainwindow.h"

/**
 * CONSTRUCTOR
 *
 * @brief MainWindow::MainWindow : Constructor for MainWindow class
 * @param parent
 */
MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    send_button = new QPushButton(this);
    send_button->setGeometry(100,200,180,50);
    send_button->setText("Send message to all clients");
    _msg = new QLineEdit(this);
    _msg->setGeometry(13,175,371,20);

    connect(ui->lancement_serveur, SIGNAL(clicked()), this, SLOT(state()));
    connect(send_button, SIGNAL(clicked()), this, SLOT(send()));
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
    delete send_button;
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
    } else if (ui->lancement_serveur->text() == QString("Arrêt Serveur")) {
        ui->lancement_serveur->setText("Lancement Serveur");
        delete serveur;
        serveur = nullptr;
    }
}

/**
 * SLOT ->
 *
 * @brief MainWindow::send : TODO
 */
void MainWindow::send() {
    if (serveur) {
        Message msg;
        msg.decodeData(get_msg());
        if (!msg.getError())
            serveur->sendToAllComputers(msg);
        else
            write_in_konsole("ERROR : " + msg.encodeData());
        _msg->clear();
        // __75&type:S&id_sender:0&id_concern:1&id_dest:1&75//
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
