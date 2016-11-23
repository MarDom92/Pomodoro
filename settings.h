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

    private slots:
        void on_buttonBox_accepted();

        void on_buttonBox_rejected();

        void on_cmbWorkTime_currentIndexChanged(int index);

    private:
        Ui::Settings *ui;

        void setCmbWorkTime();

};

#endif // SETTINGS_H
