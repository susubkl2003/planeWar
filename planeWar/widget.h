#ifndef WIDGET_H
#define WIDGET_H
#include "config.h"
#include <QWidget>
#include <QTimer>
#include "map.h"
#include <QPainter>
#include "heroplane.h"
#include <QMouseEvent>
#include "enemyplane.h"
#include "bomb.h"
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QUrl>
#include <QPixmap>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //初始化场景
    void intnconfig();

    //启动游戏
    void playGame();

    //更新所有游戏中元素的坐标
    void updatePosition();

    //绘制到屏幕中  函数名称不可改
    void paintEvent(QPaintEvent *event);

    QTimer m_Timer;//定时器

    //飞机对象
    HeroPlane m_hero;
    bool hero_index=0;

    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event);

    //敌机出场
    void enemyToScene();

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    //敌机出场间隔记录
    int m_recorder;

    //碰撞检测
    void collisionDetection();

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];

    //播放音乐
    QAudioOutput audioOutput[SOUND_MAX];
    //再来一个媒体播放器对象
    QMediaPlayer mediaPlayer[SOUND_MAX];
    //播放器数量
    int boom_index=0;
    //生命值
    QPixmap m_life[4];

    //得分
    int m_score=0;
    //生命值
    int life_index=3;
    //生命值闪烁次数
    int life_jump=GAME_LIFE_JUMP_COUNT;
    //生命值闪烁
    bool life_jump_2=0;
    //生命值闪烁间隔
    int life_space=GAME_LIFE_JUMP_SPACE;
    //生命值闪烁间隔切换
    bool life_space_change=0;
    //死亡信号
signals:
    void dead();
    //死亡槽函数
public slots:
    //槽函数需要声明，需要实现
    void deaded(Widget* w);



private:
    Ui::Widget *ui;
    Map m_map;
};
#endif // WIDGET_H
