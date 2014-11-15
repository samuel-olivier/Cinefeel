#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "APIConnector.h"
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void    updateColor();

private:
    Ui::MainWindow* ui;
    APIConnector*   _api;
    QTime           _start;
};

#endif // MAINWINDOW_H
