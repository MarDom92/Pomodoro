#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    setCmbBreakTime();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_buttonBox_accepted()
{
    //TODO add code confirm change application settings

    this->close();
}

void Settings::on_buttonBox_rejected()
{
    this->close();
}

void Settings::on_cmbWorkTime_currentIndexChanged(int index)
{
    setCmbBreakTime();
}

void Settings::setCmbBreakTime()
{
    int valueCmbBreakTime = ui->cmbWorkTime->currentText().toInt() / 5;
    ui->lblBreakTime->setText(QString::number(valueCmbBreakTime));
}
