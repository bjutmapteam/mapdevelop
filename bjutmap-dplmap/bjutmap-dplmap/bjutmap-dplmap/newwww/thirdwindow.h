#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include "mainwindow.h"

namespace Ui {
class ThirdWindow;
}

class ThirdWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThirdWindow(QWidget *parent = nullptr);
    ~ThirdWindow();

private slots:
    void goToThirdWindow();

private:
    Ui::ThirdWindow *ui;
    QLabel *label31;
};

#endif // THIRDWINDOW_H
