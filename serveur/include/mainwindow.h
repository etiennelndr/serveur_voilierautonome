#ifndef MAINWINDOW_H
#define MAINWINDOW_H 1

#include "ui_mainwindow.h"
#include <QPushButton>
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

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent=nullptr);
        ~MainWindow();
        void write_in_konsole(QString log);
        QString get_msg();

    private:
        Ui::MainWindow* ui;
    //    QPlainTextEdit *_konsole;
        QLineEdit *_msg;

        ServeurTcp* serveur=nullptr;

    public slots:
        void state();
        void msg_processing(QString msg);
        void start_uart();
        void exportDatas();
        void resetDB();
};

/**
 * METHOD
 *
 * @brief MainWindow::get_msg : TODO
 * @return
 */
inline QString MainWindow::get_msg(){ return _msg->text(); }

#endif // MAINWINDOW_H
