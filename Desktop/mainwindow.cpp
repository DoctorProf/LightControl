#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_color_clicked()
{
    QColorDialog color;
    color.exec();
}
void MainWindow::on_brightness_actionTriggered(int action)
{
    ui->brightnessLabel->setText(QString::number(ui->brightness->value()));
}


void MainWindow::on_speed_actionTriggered(int action)
{
    ui->speedLabel->setText(QString::number(ui->speed->value()));
}

