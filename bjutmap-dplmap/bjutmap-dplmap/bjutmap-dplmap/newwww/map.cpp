#include "map.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>
#include <QCursor>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "navigationwindow.h"

map::map(QWidget *parent) : QWidget(parent), scaleFactor(1.0) {
    originalMap.load(":/bjutmap.jpg");
    if (originalMap.isNull()) {
        qWarning() << "Failed to load map image!";
        return;
    }

    originalMap = originalMap.scaled(originalMap.size() / 3, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    scaledMapSize = originalMap.size();

    scaledMapPixmap = originalMap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 10, 10);

    navigateButton = new QPushButton("开始导航", this);
    navigateButton->setFixedSize(100, 70);
    mainLayout->addWidget(navigateButton, 0, Qt::AlignTop | Qt::AlignLeft);

    connect(navigateButton, &QPushButton::clicked, this, [this]() {
        NavigationWindow *navWindow = new NavigationWindow(this);
        connect(navWindow, &NavigationWindow::pathGenerated, this, &map::drawPath);
        navWindow->exec();
    });

    loadBuildingsData();
}

QSize map::getMapSize() const {
    return scaledMapSize; // 返回缩放后的地图大小
}

void map::loadBuildingsData() {
    QFile file(":/buildings_data_first_197.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open buildings data file!";
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        qWarning() << "Invalid JSON data format!";
        return;
    }

    buildingsData = doc.array();
}

void map::drawPath(const std::vector<int>& path) {
    this->path = path;
    update(); // 请求重绘
}

void map::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    int windowWidth = event->size().width();
    int windowHeight = event->size().height();
    double widthScale = static_cast<double>(windowWidth) / scaledMapSize.width();
    double heightScale = static_cast<double>(windowHeight) / scaledMapSize.height();
    scaleFactor = qMin(widthScale, heightScale);

    int newWidth = static_cast<int>(scaledMapSize.width() * scaleFactor);
    int newHeight = static_cast<int>(scaledMapSize.height() * scaleFactor);
    scaledMapPixmap = originalMap.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    update();
}

void map::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int offsetX = (width() - scaledMapPixmap.width()) / 2;
    int offsetY = (height() - scaledMapPixmap.height()) / 2;

    painter.drawPixmap(offsetX, offsetY, scaledMapPixmap);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::yellow);

    // 绘制建筑物
    for (const QJsonValue &buildingValue : buildingsData) {
        QJsonObject building = buildingValue.toObject();
        QString name = building["name"].toString();
        QJsonArray positionArray = building["position"].toArray();
        if (positionArray.size() == 2) {
            int x = positionArray[0].toInt();
            int y = positionArray[1].toInt();
            QPoint buildingPos(x * scaleFactor / 3, y * scaleFactor / 3);
            painter.drawEllipse(buildingPos + QPoint(offsetX, offsetY), 5, 5);
            painter.drawText(buildingPos + QPoint(5, -5) + QPoint(offsetX, offsetY), name);
        }
    }

    // 绘制路径
    painter.setPen(Qt::red);
    for (size_t i = 1; i < path.size(); ++i) {
        int startIndex = path[i - 1] - 1; // 使用 path 中的节点直接索引
        int endIndex = path[i] - 1;

        QJsonObject startBuilding = buildingsData[startIndex].toObject();
        QJsonObject endBuilding = buildingsData[endIndex].toObject();
        QJsonArray startPos = startBuilding["position"].toArray();
        QJsonArray endPos = endBuilding["position"].toArray();
        if (startPos.size() == 2 && endPos.size() == 2) {
            int startX = startPos[0].toInt() * scaleFactor / 3 + offsetX;
            int startY = startPos[1].toInt() * scaleFactor / 3 + offsetY;
            int endX = endPos[0].toInt() * scaleFactor / 3 + offsetX;
            int endY = endPos[1].toInt() * scaleFactor / 3 + offsetY;
            painter.drawLine(startX, startY, endX, endY); // 绘制路径线段
        }
    }
}
