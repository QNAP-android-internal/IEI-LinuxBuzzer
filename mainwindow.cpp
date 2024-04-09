#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QDebug>
#include <QFontComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QThread>
#include <QString>
#include <QStringList>
#include <QProcess>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString style = "QSlider::groove:horizontal {"

                    "height: 30px;"
                    "background-color: #000000;"
                    "}"
                    "QSlider::handle:horizontal {"
                    "width: 30px;"
                    "height: 30px;"
                    "background-color: #FF0000;"
                    "}";
    ui->controlSlider->setStyleSheet(style);
}

MainWindow::~MainWindow()
{
    QProcess p;
    QString printf = "echo 0 > /sys/class/backlight/buzzer_pwm/brightness | sudo -S";
    p.start("bash", QStringList() <<"-c" <<printf);
    p.waitForFinished();
    p.kill();
    delete ui;
}


void MainWindow::on_controlSlider_sliderMoved(int position)
{
    ui->controlSlider->setMinimum(0);
    ui->controlSlider->setMaximum(50);
    QString index = QString::number(position);
    QProcess p;
    QString printf = "echo " + index + " > /sys/class/backlight/buzzer_pwm/brightness | sudo -S";
    p.start("bash", QStringList() <<"-c" <<printf);
    p.waitForFinished();
    p.kill();
    ui->txt_volume->setText("value:"+index);
}



void MainWindow::on_pushButton_clicked()
{
    QProcess p;
    QString printf = "echo 0 > /sys/class/backlight/buzzer_pwm/brightness | sudo -S";
    p.start("bash", QStringList() <<"-c" <<printf);
    p.waitForFinished();
    p.kill();
    MainWindow::close();
}

