#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include "map.h"

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit FirstWindow(QWidget *parent = nullptr);
    ~FirstWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;  // 重载resizeEvent函数

private slots:
    void goToFirstWindow();

private:
    Ui::FirstWindow *ui;
    map *mapWidget;   // 地图部件
    QPushButton *button11;  // 左下角按钮
};

#endif // FIRSTWINDOW_H
