#include "thirdwindow.h"
#include "ui_thirdwindow.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>


ThirdWindow::ThirdWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ThirdWindow)
{
    ui->setupUi(this);

    label31 = new QLabel(this);
    QPixmap pixmap31(":/shzn333.png"); // 替换为第二张图片的实际路径
    pixmap31 = pixmap31.scaled(1191, 1086, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label31->setPixmap(pixmap31);
    label31->setGeometry(0, 0, 1191,1086); // 设置位置和大小，确保不重叠


    QPushButton *button31 = new QPushButton(this);
    QIcon icon(":/zydz.png");
    button31->setIcon(icon);
    button31->move(0,906);
    button31->resize(180,180);
    button31->setIconSize(QSize(180, 180));
    connect(button31,SIGNAL(clicked(bool)),this,SLOT(goToThirdWindow()));
}

ThirdWindow::~ThirdWindow()
{
    delete ui;
}

void ThirdWindow::goToThirdWindow() {
    MainWindow *mai = new MainWindow;
    mai->show();
    this->hide();
}
