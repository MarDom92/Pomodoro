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

    valueWorkTime = 30 * 60;
    valueBreakTime = valueWorkTime / 5;

    workTime = valueWorkTime;
    breakTime = valueBreakTime;

    caseTime = false;

    palette = new QPalette();
    color = 3;
    setColorLblTime();
}

MainWindow::~MainWindow()
{
    delete timer;

    delete ui;
}

void MainWindow::on_btnSettings_clicked()
{
    settings = new Settings;

    connect(settings, SIGNAL(pressedButtonBox()), this, SLOT(updateLabels()));
    settings->setTimes(valueWorkTime);
    settings->setColor(color);

    settings->exec();
}

void MainWindow::on_btnStart_clicked()
{
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

            workTime = valueWorkTime;
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

            breakTime = valueBreakTime;

            ui->btnStart->setEnabled(true);
            ui->btnSettings->setEnabled(true);
        }
    }
}

void MainWindow::updateLabels()
{
    valueWorkTime = settings->getWorkTime() * 60;
    valueBreakTime = valueWorkTime / 5;

    workTime = valueWorkTime;
    breakTime = valueBreakTime;

    int workTimeMinutes = workTime / 60;

    ui->lblTitle->setText("Czas pracy:");

    QString strWorkTimeMinutes;

    if(workTimeMinutes > 9)
        strWorkTimeMinutes = QString::number(workTimeMinutes);
    else
        strWorkTimeMinutes = "0" + QString::number(workTimeMinutes);

    ui->lblTime->setText(strWorkTimeMinutes + ":00");

    color = settings->getColor();
    setColorLblTime();
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

void MainWindow::setColorLblTime()
{
    switch(color)
    {
        case 0:
            palette->setColor(QPalette::WindowText, Qt::white);
        break;

        case 1:
            palette->setColor(QPalette::WindowText, Qt::black);
        break;

        case 2:
            palette->setColor(QPalette::WindowText, QColor(244, 67, 54));
        break;

        case 3:
            palette->setColor(QPalette::WindowText, QColor(63, 81, 181));
        break;

        case 4:
            palette->setColor(QPalette::WindowText, QColor(76, 175, 80));
        break;
    }

    ui->lblTime->setPalette(*palette);
}
