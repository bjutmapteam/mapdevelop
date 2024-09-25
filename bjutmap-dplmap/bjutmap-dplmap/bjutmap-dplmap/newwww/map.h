#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QPushButton>
#include <QJsonArray>
#include <QLineEdit>
#include <QVBoxLayout>
#include <vector>

class map : public QWidget {
    Q_OBJECT

public:
    explicit map(QWidget *parent = nullptr);
    QSize getMapSize() const;

signals:
    void pathGenerated(const std::vector<int>& path);  // 路径生成信号

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap originalMap;
    QPixmap scaledMapPixmap;
    QSize scaledMapSize;
    QJsonArray buildingsData;

    QVBoxLayout *mainLayout;
    QPushButton *navigateButton;

    double scaleFactor;
    std::vector<int> path;  // 用于存储路径数据

    void loadBuildingsData();
    void drawPath(const std::vector<int>& path);  // 绘制路径的函数
};

#endif // MAP_H
