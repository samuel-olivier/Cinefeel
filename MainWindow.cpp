#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <QtMath>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _api(new APIConnector())
{
    _api->setHost("192.168.3.7:34000");

    ui->setupUi(this);
    QTimer *updateTimer = new QTimer(this);

    connect(updateTimer, SIGNAL(timeout()), SLOT(updateColor()));
    updateTimer->start(100);
    _start.restart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateColor()
{
    float resSin = 0.5 + 0.5 * qSin(float(_start.elapsed()) / 1000.);
    _api->setTemperature(resSin * 100);
}
