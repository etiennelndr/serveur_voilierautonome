#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->lancement_serveur, SIGNAL(clicked()), this, SLOT(state()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete serveur;
}

void MainWindow::state() {
    if (ui->lancement_serveur->text() == QString("Lancement Serveur")) {
        ui->lancement_serveur->setText("Arrêt Serveur");
        serveur = new ServeurTcp (4000);
    } else if (ui->lancement_serveur->text() == QString("Arrêt Serveur")) {
        ui->lancement_serveur->setText("Lancement Serveur");
        delete serveur;
    }
}
