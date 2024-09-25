#include "firstwindow.h"
#include "ui_firstwindow.h"
#include "mainwindow.h"
#include "map.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow),
    mapWidget(new map(this)),  // 创建地图部件
    button11(new QPushButton(this))  // 创建按钮并初始化
{
    ui->setupUi(this);

    // 设置窗口初始大小为缩小后的地图大小
    resize(mapWidget->getMapSize());

    // 设置按钮图标及其大小
    QIcon icon(":/zydz.png");
    button11->setIcon(icon);
    button11->resize(100, 100);  // 设置按钮大小
    button11->setIconSize(QSize(100, 100));

    // 设置按钮位置到窗口左下角
    button11->move(10, height() - button11->height() - 10);

    // 连接按钮点击信号到槽函数
    connect(button11, &QPushButton::clicked, this, &FirstWindow::goToFirstWindow);

    // 设置地图为中央小部件
    setCentralWidget(mapWidget);  // 将mapWidget设置为窗口的中央小部件
}

void FirstWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    // 在窗口大小变化时，移动按钮到左下角
    button11->move(10, height() - button11->height() - 10);
}

FirstWindow::~FirstWindow() {
    delete ui;
}

void FirstWindow::goToFirstWindow() {
    MainWindow *mai = new MainWindow;
    mai->show();
    this->hide();  // 隐藏当前窗口
}
