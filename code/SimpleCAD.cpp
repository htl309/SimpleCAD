#include <QtWidgets/QApplication>  // 必须，包含 QApplication 类
#include <QtWidgets/QPushButton>   // 可选，包含按钮类
#include "CADWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    CADWindow w;

    w.show();                // 显示按钮

    return a.exec();  // 运行事件循环
}
