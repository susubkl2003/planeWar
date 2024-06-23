#include "widget.h"
#include <QResource>
#include <QApplication>
#include "config.h"
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //注册二进制文件
//    QResource::registerResource(GAME_RES_PATH);
    Widget w;
    w.show();
    QObject::connect(&w, &Widget::dead, [&w]() {
        w.deaded(&w);
//        w.close();
//        QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "游戏结束", "小笨蛋这都能输，行不行啊你\nYES:重新开始  NO:退出游戏");
//        if(ret==QMessageBox::Yes)
//        {
//            w.m_score=0;
//            w.life_index=3;
//           w.playGame();
//        }

    });
    return a.exec();
}
