#ifndef NAVIGATIONWINDOW_H
#define NAVIGATIONWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>
#include <string>

class NavigationWindow : public QDialog {
    Q_OBJECT

public:
    explicit NavigationWindow(QWidget *parent = nullptr);

signals:
    void pathGenerated(const std::vector<int>& path);  // 添加路径生成信号

private:
    QLineEdit *startPointEdit; // 起始点输入框
    QLineEdit *endPointEdit;   // 终点输入框
    QPushButton *submitButton;  // 提交按钮

    void processPath(const std::string& startBuilding, const std::string& endBuilding, std::vector<int>& path);
    std::string pathToString(const std::vector<int>& path);
    void storePath(int node, const std::vector<int>& previousNode, std::vector<int>& path);
};

#endif // NAVIGATIONWINDOW_H
