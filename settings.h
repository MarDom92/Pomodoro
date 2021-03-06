#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QString>

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
        Q_OBJECT

    public:
        explicit Settings(QWidget *parent = 0);
        ~Settings();

        int getWorkTime();

        void setTimes(int wTime);

        int getColor();

        void setColor(int c);

        int getVolume();

        void setVolume(int v);

    private slots:
        void on_buttonBox_accepted();

        void on_buttonBox_rejected();

        void on_cmbWorkTime_currentIndexChanged(int index);

        void on_cmbColor_activated(int index);

        void on_sliderVolume_valueChanged(int value);

    signals:
        void pressedButtonBox();

    private:
        Ui::Settings *ui;

        int workTime, breakTime;

        int color, volume;
};

#endif // SETTINGS_H
