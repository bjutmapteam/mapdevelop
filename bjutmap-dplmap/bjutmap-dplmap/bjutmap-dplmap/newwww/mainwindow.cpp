#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    label0 = new QLabel(this);
    QPixmap pixmap0(":/newback.jpg"); // 替换为图片的实际路径
    pixmap0 = pixmap0.scaled(1900, 1900, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label0->setPixmap(pixmap0);
    label0->setGeometry(0, 0, 1280, 1280); // 设置位置和大小

    // 初始化第一个QLabel
    label1 = new QLabel(this);
    QPixmap pixmap1(":/titlen.png"); // 替换为图片的实际路径
    pixmap1 = pixmap1.scaled(1280, 2560, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label1->setPixmap(pixmap1);
    label1->setGeometry(0, 0, 1600, 400); // 设置位置和大小

    // 初始化第二个QLabel
    label2 = new QLabel(this);
    QPixmap pixmap2(":/nnnnnziti.png"); // 替换为第二张图片的实际路径
    pixmap2 = pixmap2.scaled(960, 1920, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label2->setPixmap(pixmap2);
    label2->setGeometry(150, 200, 1600, 650); // 设置位置和大小，确保不重叠


    /*label3 = new QLabel(this);
    QPixmap pixmap3(":/ksdh.png"); // 替换为第3张图片的实际路径
    pixmap3 = pixmap3.scaled(400, 800, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label3->setPixmap(pixmap3);
    label3->setGeometry(150, 500, 1600, 650); // 设置位置和大小，确保不重叠*/



    /*label4 = new QLabel(this);
    QPixmap pixmap4(":/xyfm.png"); // 替换为第4张图片的实际路径
    pixmap4 = pixmap4.scaled(400, 800, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label4->setPixmap(pixmap4);
    label4->setGeometry(730, 500, 1600, 650); // 设置位置和大小，确保不重叠*/

    /*label5 = new QLabel(this);
    QPixmap pixmap5(":/shzn.png"); // 替换为第5张图片的实际路径
    pixmap5 = pixmap5.scaled(400, 800, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label5->setPixmap(pixmap5);
    label5->setGeometry(150, 755, 1600, 650); // 设置位置和大小，确保不重叠*/

    /*label6 = new QLabel(this);
    QPixmap pixmap6(":/gdyww.png"); // 替换为第6张图片的实际路径
    pixmap6 = pixmap6.scaled(410, 820, Qt::KeepAspectRatio); // 调整大小，保持宽高比
    label6->setPixmap(pixmap6);
    label6->setGeometry(730, 750, 1600, 650); // 设置位置和大小，确保不重叠*/

    QPushButton *button4 = new QPushButton(this);
    QIcon icon4(":/gdywsec.png");
    button4->setIcon(icon4);
    button4->move(730,1000);
    button4->resize(400,160);
    button4->setIconSize(QSize(420, 200));
    connect(button4,SIGNAL(clicked(bool)),this,SLOT(goToForthWindow()));

    QPushButton *button3 = new QPushButton(this);
    QIcon icon3(":/shznsec.png");
    button3->setIcon(icon3);
    button3->move(150,1000);
    button3->resize(400,160);
    button3->setIconSize(QSize(420, 200));
    connect(button3,SIGNAL(clicked(bool)),this,SLOT(goToThirdWindow()));

    QPushButton *button1 = new QPushButton(this);
    QIcon icon1(":/ksdhsec.png");
    button1->setIcon(icon1);
    button1->move(150,745);
    button1->resize(400,160);
    button1->setIconSize(QSize(420, 200));
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(goToFirstWindow()));

    QPushButton *button2 = new QPushButton(this);
    QIcon icon2(":/secxyfm.png");
    button2->setIcon(icon2);
    button2->move(730,745);
    button2->resize(400,160);
    button2->setIconSize(QSize(420, 200));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(change()));

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: change(){
    SecondWindow *sec = new SecondWindow;
    sec->show();
    this->hide();
}

void MainWindow:: goToFirstWindow(){
    FirstWindow *fir = new FirstWindow;
    fir->show();
    this->hide();
}

void MainWindow:: goToThirdWindow(){
    ThirdWindow *thr = new ThirdWindow;
    thr->show();
    this->hide();
}

void MainWindow:: goToForthWindow(){
    ForthWindow *four = new ForthWindow;
    four->show();
    this->hide();
}
