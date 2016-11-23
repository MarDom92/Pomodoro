#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QString>
#include <QTimer>
#include "settings.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_btnSettings_clicked();

        void on_btnStart_clicked();

        void updateLblTime();

    private:
        Ui::MainWindow *ui;

        Settings *settings;

        QTimer *timer;

        //false - work, true - break
        bool caseTime;

        unsigned int workTime, breakTime;

        void updateWorkTime();

        void updateBreakTime();
};

#endif // MAINWINDOW_H
