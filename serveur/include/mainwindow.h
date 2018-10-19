#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QObject>

#include "serveur.h"
class QPushButton;
class QTextEdit;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent=nullptr);
    ~MainWindow();
    QString get_msg(){ return _msg->text(); }
    void write_in_konsole(QString log) {_konsole->appendPlainText(log);}

private:
    Ui::MainWindow* ui;
    QPlainTextEdit *_konsole;
    QPushButton *send_button;
    QLineEdit *_msg;

    ServeurTcp* serveur=nullptr;

public slots:
    void state();
    void send();
    void msg_processing(QString msg);
};

#endif // MAINWINDOW_H
