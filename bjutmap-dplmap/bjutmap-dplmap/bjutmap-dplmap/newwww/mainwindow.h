#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>
#include "firstwindow.h"
#include "secondwindow.h"
#include "thirdwindow.h"
#include "forthwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void change();
    void goToFirstWindow();
    void goToForthWindow();
    void goToThirdWindow();
private:
    Ui::MainWindow *ui;
    QLabel *label0;
    QLabel *label1; // 用于显示第一张图片
    QLabel *label2; // 用于显示第二张图片
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QStackedWidget *stackedWidget; // 声明QStackedWidget指针


};
#endif // MAINWINDOW_H
