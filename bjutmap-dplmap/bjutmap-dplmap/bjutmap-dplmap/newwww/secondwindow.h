#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include "mainwindow.h"

namespace Ui {
class SecondWindow;
}

class SecondWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SecondWindow(QWidget *parent = nullptr);
    ~SecondWindow();

private slots:
    void change();

private:
    Ui::SecondWindow *ui;
    QLabel *label21;
};

#endif // SECONDWINDOW_H
