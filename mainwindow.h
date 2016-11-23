#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QSettings>
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

        void updateWorkTime();

        void updateBreakTime();

        void setColorLblTime();

        void saveSystemSettings();

        void loadSystemSettings();

    private slots:
        void on_btnSettings_clicked();

        void on_btnStart_clicked();

        void updateLblTime();

        void updateValues();

    private:
        Ui::MainWindow *ui;

        Settings *settings;

        QTimer *timer;

        //false - work, true - break
        bool caseTime;

        unsigned int workTime, breakTime, valueWorkTime, valueBreakTime;

        QPalette *palette;

        int color, volume;
};

#endif // MAINWINDOW_H
