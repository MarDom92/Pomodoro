#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateLblTime()));

    workTime = 30 * 60;
    breakTime = workTime / 6;

    caseTime = false;
}

MainWindow::~MainWindow()
{
    delete timer;
    delete settings;

    delete ui;
}

void MainWindow::on_btnSettings_clicked()
{
    settings = new Settings;
    settings->exec();
}

void MainWindow::on_btnStart_clicked()
{
    workTime = 30 * 60;
    breakTime = workTime / 6;

    caseTime = false;

    timer->start();

    ui->btnStart->setEnabled(false);
    ui->btnSettings->setEnabled(false);
}

void MainWindow::updateLblTime()
{
    //work
    if(!caseTime)
    {
        ui->lblTitle->setText("Czas pracy:");

        updateWorkTime();

        if(workTime == 0)
        {
            caseTime = true;
        }
    }
    //break
    else
    {
        ui->lblTitle->setText("Czas przerwy:");

        updateBreakTime();

        if(breakTime == 0)
        {
            timer->stop();

            ui->btnStart->setEnabled(true);
            ui->btnSettings->setEnabled(true);
        }
    }
}

void MainWindow::updateWorkTime()
{
    if(workTime > 0)
    {
        workTime--;

        int workTimeMinutes = workTime / 60;
        int workTimeSeconds = workTime % 60;

        QString strWorkTimeMinutes;
        QString strWorkTimeSeconds;

        if(workTimeMinutes > 9)
            strWorkTimeMinutes = QString::number(workTimeMinutes);
        else
            strWorkTimeMinutes = "0" + QString::number(workTimeMinutes);

        if(workTimeSeconds > 9)
            strWorkTimeSeconds = QString::number(workTimeSeconds);
        else
            strWorkTimeSeconds = "0" + QString::number(workTimeSeconds);

        ui->lblTime->setText(strWorkTimeMinutes + ":" + strWorkTimeSeconds);
    }
}

void MainWindow::updateBreakTime()
{
    if(breakTime > 0)
    {
        breakTime--;

        int breakTimeMinutes = breakTime / 60;
        int breakTimeSeconds = breakTime % 60;

        QString strBreakTimeMinutes;
        QString strBreakTimeSeconds;

        if(breakTimeMinutes > 9)
            strBreakTimeMinutes = QString::number(breakTimeMinutes);
        else
            strBreakTimeMinutes = "0" + QString::number(breakTimeMinutes);

        if(breakTimeSeconds > 9)
            strBreakTimeSeconds = QString::number(breakTimeSeconds);
        else
            strBreakTimeSeconds = "0" + QString::number(breakTimeSeconds);

        ui->lblTime->setText(strBreakTimeMinutes + ":" + strBreakTimeSeconds);
    }
}
