#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings()
{
    delete ui;

    delete this;
}

void Settings::on_buttonBox_accepted()
{
    emit pressedButtonBox();

    this->close();
}

void Settings::on_buttonBox_rejected()
{
    this->close();
}

void Settings::on_cmbWorkTime_currentIndexChanged(int index)
{
    workTime = ui->cmbWorkTime->currentText().toInt();
    breakTime = workTime / 5;

    ui->lblBreakTime->setText(QString::number(breakTime));
}

int Settings::getWorkTime()
{
    return workTime;
}

void Settings::setTimes(int wTime)
{
    workTime = wTime / 60;
    breakTime = workTime / 5;

    ui->cmbWorkTime->setCurrentText(QString::number(workTime));
    ui->lblBreakTime->setText(QString::number(breakTime));
}

int Settings::getColor()
{
    return color;
}

void Settings::setColor(int c)
{
    color = c;

    ui->cmbColor->setCurrentIndex(color);
}

int Settings::getVolume()
{
    return volume;
}

void Settings::setVolume(int v)
{
    volume = v;

    ui->sliderVolume->setValue(volume);
}

void Settings::on_cmbColor_activated(int index)
{
    color = ui->cmbColor->currentIndex();
}

void Settings::on_sliderVolume_valueChanged(int value)
{
    volume = value;
}
