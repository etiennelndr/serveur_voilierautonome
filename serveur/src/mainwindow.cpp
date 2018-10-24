#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    send_button = new QPushButton(this);
    send_button->setGeometry(100,200,180,50);
    send_button->setText("Send message to all clients");
    _msg = new QLineEdit(this);
    _msg->setGeometry(140,175,100,20);

    connect(ui->lancement_serveur, SIGNAL(clicked()), this, SLOT(state()));
    connect(send_button, SIGNAL(clicked()), this, SLOT(send()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete serveur;
    delete _msg;
    delete send_button;
}

void MainWindow::write_in_konsole(QString log) {
    ui->konsole->appendPlainText(log);
}

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

void MainWindow::send() {
    serveur->envoyerATous(_msg->text());
    _msg->clear();
    if (serveur)
        serveur->envoyerATous(get_msg());
}

void MainWindow::msg_processing(QString msg){
    write_in_konsole(msg);
}
