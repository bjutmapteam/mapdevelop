#include "mainwindow.h"
#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>

SecondWindow::SecondWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    //QLabel *label = new QLabel(this);
    //label->setText(" ");


    label21 = new QLabel(this);
    QPixmap pixmap21(":/qjt.png"); // 替换为第二张图片的实际路径
    pixmap21 = pixmap21.scaled(1648, 1000, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label21->setPixmap(pixmap21);
    label21->setGeometry(0, 0, 1648,1000); // 设置位置和大小，确保不重叠

    QPushButton *button21 = new QPushButton(this);
    QIcon icon(":/zydz.png");
    button21->setIcon(icon);
    button21->move(0,800);
    button21->resize(200,200);
    button21->setIconSize(QSize(200, 200));
    connect(button21,SIGNAL(clicked(bool)),this,SLOT(change()));


}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::change() {
    MainWindow *mai = new MainWindow;
    mai->show();
    this->hide();
}
