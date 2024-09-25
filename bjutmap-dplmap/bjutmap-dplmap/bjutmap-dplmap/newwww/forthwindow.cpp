#include "forthwindow.h"
#include "ui_forthwindow.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>


ForthWindow::ForthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ForthWindow)
{
    ui->setupUi(this);

    label40 = new QLabel(this);
    QPixmap pixmap40(":/newback.jpg"); // 替换为图片的实际路径
    pixmap40 = pixmap40.scaled(1900, 1900, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label40->setPixmap(pixmap40);
    label40->setGeometry(0, 0, 1280, 1280); // 设置位置和大小

    label41 = new QLabel(this);
    QPixmap pixmap41(":/xym.png"); // 替换为图片的实际路径
    pixmap41 = pixmap41.scaled(600, 600, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label41->setPixmap(pixmap41);
    label41->setGeometry(50, 250, 600, 600); // 设置位置和大小

    label42 = new QLabel(this);
    QPixmap pixmap42(":/lxwm.png"); // 替换为图片的实际路径
    pixmap42 = pixmap42.scaled(600, 600, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label42->setPixmap(pixmap42);
    label42->setGeometry(400, 870, 600, 600); // 设置位置和大小

    label43 = new QLabel(this);
    QPixmap pixmap43(":/gzh.png"); // 替换为图片的实际路径
    pixmap43 = pixmap43.scaled(900, 900, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label43->setPixmap(pixmap43);
    label43->setGeometry(600, 50, 900, 900); // 设置位置和大小

    QPushButton *button41 = new QPushButton(this);
    QIcon icon(":/zydz.png");
    button41->setIcon(icon);
    button41->move(0,1050);
    button41->resize(200,200);
    button41->setIconSize(QSize(200, 200));
    connect(button41,SIGNAL(clicked(bool)),this,SLOT(goToForthWindow()));
}

ForthWindow::~ForthWindow()
{
    delete ui;
}

void ForthWindow::goToForthWindow() {
    MainWindow *mai = new MainWindow;
    mai->show();
    this->hide();
}
