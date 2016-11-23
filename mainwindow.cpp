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

    loadSystemSettings();

    workTime = valueWorkTime;
    breakTime = valueBreakTime;

    caseTime = false;

    palette = new QPalette();
    setColorLblTime();
}

MainWindow::~MainWindow()
{
    saveSystemSettings();

    delete timer;

    delete ui;
}

void MainWindow::on_btnSettings_clicked()
{
    settings = new Settings;

    connect(settings, SIGNAL(pressedButtonBox()), this, SLOT(updateValues()));
    settings->setTimes(valueWorkTime);
    settings->setColor(color);
    settings->setVolume(volume);

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

void MainWindow::updateValues()
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

    volume = settings->getVolume();
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

void MainWindow::saveSystemSettings()
{
    //organization's name and application's name
    QSettings systemSettings("MD", "Pomodoro");

    systemSettings.beginGroup("MainWindow");

    systemSettings.setValue("geometry", saveGeometry());
    systemSettings.setValue("state", saveState());
    systemSettings.setValue("maximize", isMaximized());
    systemSettings.setValue("valueWorkTime", valueWorkTime);
    systemSettings.setValue("valueBreakTime", valueBreakTime);
    systemSettings.setValue("color", color);
    systemSettings.setValue("volume", volume);

    if(!isMaximized())
    {
        systemSettings.setValue("position", pos());
        systemSettings.setValue("size", size());
    }

    systemSettings.endGroup();
}

void MainWindow::loadSystemSettings()
{
    //organization's name and application's name
    QSettings systemSettings("MD", "Pomodoro");

    systemSettings.beginGroup("MainWindow");

    restoreGeometry(systemSettings.value("geometry", saveGeometry()).toByteArray());
    restoreState(systemSettings.value("state", saveState()).toByteArray());
    move(systemSettings.value("position", pos()).toPoint());
    resize(systemSettings.value("size", size()).toSize());

    valueWorkTime = systemSettings.value("valueWorkTime").toInt();
    valueBreakTime = systemSettings.value("valueBreakTime").toInt();
    color = systemSettings.value("color").toInt();
    volume = systemSettings.value("volume").toInt();

    if(systemSettings.value("maximize", isMaximized()).toBool())
        showMaximized();

    systemSettings.endGroup();
}
