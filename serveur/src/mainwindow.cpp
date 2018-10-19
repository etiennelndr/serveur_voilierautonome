#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    send_button = new QPushButton(this);
    send_button->setGeometry(100,100,180,50);
    send_button->setText("Send message to all clients");
    _msg = new QLineEdit(this);
    _msg->setGeometry(140,175,100,20);
    _konsole = new QPlainTextEdit(this);
    _konsole->setGeometry(40,325,300,200);
    _konsole->setReadOnly(true);

    connect(ui->lancement_serveur, SIGNAL(clicked()), this, SLOT(state()));
    connect(send_button, SIGNAL(clicked()), this, SLOT(send()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete serveur;
    delete _konsole;
    delete _msg;
    delete send_button;
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
    if (serveur)
        serveur->envoyerATous(get_msg());
}

void MainWindow::msg_processing(QString msg){
    write_in_konsole(msg);
}
