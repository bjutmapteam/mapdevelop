#ifndef FORTHWINDOW_H
#define FORTHWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include "mainwindow.h"

namespace Ui {
class ForthWindow;
}

class ForthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ForthWindow(QWidget *parent = nullptr);
    ~ForthWindow();

private slots:
    void goToForthWindow();

private:
    Ui::ForthWindow *ui;
    QLabel *label40;
    QLabel *label41;
    QLabel *label42;
    QLabel *label43;
};

#endif // FORTHWINDOW_H
