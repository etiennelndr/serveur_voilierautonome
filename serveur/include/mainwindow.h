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
        Ui::MainWindow* ui = nullptr;
    //    QPlainTextEdit *_konsole;
        QLineEdit *_msg = nullptr;

        ServeurTcp* serveur= nullptr;

        bool isResettingDatabase;
        bool isExportingDatabase;

    public slots:
        void state();
        void msg_processing(QString msg);
        void start_uart();
        // Exporting datas
        void exportDatas();
        // Reseting the database
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
