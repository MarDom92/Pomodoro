#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete settings;

    delete ui;
}

void MainWindow::on_btnSettings_clicked()
{
    settings = new Settings;
    settings->exec();
}
