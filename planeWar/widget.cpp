#include "widget.h"
#include "ui_widget.h"
#include <ctime>
#include <QSoundEffect>
#include "music.h"
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    intnconfig();
    //得分
    m_score=0;
    //生命值
    life_index=3;
    //生命值闪烁次数
    life_jump=GAME_LIFE_JUMP_COUNT;
    //生命值闪烁
    life_jump_2=0;
    //生命值闪烁间隔
    life_space=GAME_LIFE_JUMP_SPACE;
    //生命值闪烁间隔切换
    life_space_change=0;
    //死亡信号
//    m_life.load(HERO_PATH);
    //初始化生命值图片资源
    for(int i = 0 ;i <= GAME_LIFE ;i++)
    {
        //字符串拼接，类似  ":/res/bomb-1.png"
        QString str = QString(LIFE_PATH).arg(i);
        m_life[i].load(str);
    }
    //初始化加载飞机图片资源
    for(int i=0;i<SOUND_MAX;i++)
    {
        mediaPlayer[i].setAudioOutput(audioOutput+i);
        audioOutput[i].setVolume(1);
        mediaPlayer[i].setSource(
            QUrl(SOUND_BOMB));
    }

    //启动游戏
    playGame();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::intnconfig()
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);
    //设置标题图标
    setWindowIcon(QIcon(GAME_ICON));
    //定时器设置
    m_Timer.setInterval(GAME_RATE);
    m_recorder = 0;
    //随机数种子
    srand((unsigned int)time(NULL));  //头文件  #include <ctime>


}
void Widget::playGame()
{
    Music * subThread = new Music;
    subThread->start();
    Music * subThread1 = new Music;
    subThread1->start();
    Music * subThread2 = new Music;
    subThread2->start();
    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){
        //敌机出场
        enemyToScene();
        //更新游戏中元素的坐标
        updatePosition();
        //重新绘制图片
        update();
        collisionDetection();
    });


}

void Widget::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();
    //发射子弹
    m_hero.shoot();
    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!m_hero.m_bullets[i].m_Free)
        {
            m_hero.m_bullets[i].updatePosition();
        }
    }
    //敌机坐标计算
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        //非空闲敌机 更新坐标
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
        }
    }
    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            m_bombs[i].updateInfo();
        }
    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY , m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY , m_map.m_map2);
    //绘制飞机
    //绘制英雄
    if(hero_index)
    {
        painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);
        hero_index=!hero_index;
    }
    else
    {
        painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane_2);
        hero_index=!hero_index;
    }
    //绘制子弹
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!m_hero.m_bullets[i].m_Free)
        {
            painter.drawPixmap(m_hero.m_bullets[i].m_X+10,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }
    }
    //绘制敌机
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }
    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }
    //绘制生命值
    if(life_jump_2)
    {
        if(life_space_change)
        {
            painter.drawPixmap(0,0,m_life[life_index]);
            life_space--;
            life_jump--;
        }
        else
        {
            painter.drawPixmap(0,0,m_life[life_index+1]);
            life_space--;
            life_jump--;
        }
        if(life_space==0)
        {
            life_space_change=!life_space_change;
            life_space=GAME_LIFE_JUMP_SPACE;
        }
        if(life_jump==0)
        {
            life_jump=GAME_LIFE_JUMP_COUNT;
            life_jump_2=0;
        }
//        QMessageBox::information(this,"","你死了");
    }
    else
    {
        painter.drawPixmap(0,0,m_life[life_index]);
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x() - m_hero.m_Rect.width()*0.5; //鼠标位置 - 飞机矩形的一半
    int y = event->y() - m_hero.m_Rect.height()*0.5;

    //边界检测
    if(x <= 0 )
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }
    m_hero.setPosition(x,y);

}

void Widget::enemyToScene()
{
    m_recorder++;
    if(m_recorder < ENEMY_INTERVAL)
    {
        return;
    }

    m_recorder = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            //敌机空闲状态改为false
            m_enemys[i].m_Free = false;
            //设置坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }

}

void Widget::collisionDetection()
{
    //遍历所有非空闲的敌机
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        //被敌机碰到，生命值减少
        if(m_enemys[i].escaped)
        {
            if(life_index>0)
            {
                life_index--;
            }
            if(life_index==0)
            {
                emit dead();
            }
            m_enemys[i].escaped=0;
            life_jump_2=1;
        }
        if(m_enemys[i].m_Free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }
        //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
//        if(m_enemys[i].m_Rect.intersects(m_hero.m_Rect))
//        {

//            bump=1;
//        }
        //遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {

            if(m_hero.m_bullets[j].m_Free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
            {
                m_enemys[i].m_Free = true;
                m_hero.m_bullets[j].m_Free = true;
                //分数增加
                m_score++;
                ui->label->setText(QString::number(m_score));
                //播放爆炸效果
                for(int k = 0 ; k < BOMB_NUM;k++)
                {
//                    mediaPlayer->play();
                    if(boom_index<SOUND_MAX)
                    {
                        mediaPlayer[boom_index].play();
                        boom_index++;
                    }
                    else
                    {
                        boom_index=0;
                        mediaPlayer[boom_index].play();
                        boom_index++;
                    }
                    if(m_bombs[k].m_Free)
                    {
                        //爆炸状态设置为非空闲
                        m_bombs[k].m_Free = false;
                        //更新坐标

                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }

//    if(bump)
//    {
//        life_index--;
//    }

}

void Widget::deaded(Widget *w)
{
//    QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "游戏结束", "小笨蛋这都能输，行不行啊你\nYES:重新开始  NO:退出游戏");
    QMessageBox::information(this,"游戏结束","哎呀，小笨蛋这都能输，你行不行啊\n要不回家种田去吧，哎呀呀呀，行不行呀");
    w->close();
    delete w;
}
//if(ret==QMessageBox::Yes)
//{
//    m_score=0;
//    //生命值
//    life_index=3;
//    //生命值闪烁次数
//    life_jump=GAME_LIFE_JUMP_COUNT;
//    //生命值闪烁
//    life_jump_2=0;
//    //生命值闪烁间隔
//    life_space=GAME_LIFE_JUMP_SPACE;
//    //生命值闪烁间隔切换
//    life_space_change=0;


//    /**********hero属性更新***********/
//    //初始化坐标
//    m_hero.m_X = GAME_WIDTH * 0.5 - m_hero.m_Plane.width()*0.5;
//    m_hero.m_Y = GAME_HEIGHT - m_hero.m_Plane.height();

//    //初始化矩形框
//    m_hero.m_Rect.setWidth(m_hero.m_Plane.width());
//    m_hero.m_Rect.setHeight(m_hero.m_Plane.height());
//    m_hero.m_Rect.moveTo(m_hero.m_X,m_hero.m_Y);

//    //初始化发射间隔记录
//    m_hero.m_recorder = 0;

//    QPixmap m_enemy;
//    m_enemy.load(ENEMY_PATH);
//    /**********敌机属性更新***********/
//    for(int i = 0 ;i < ENEMY_NUM;i++)
//    {
//        //敌机位置
//        m_enemys[i].m_X = 0;
//        m_enemys[i].m_Y = 0;

//        //敌机状态
//        m_enemys[i].m_Free = true;

//        //敌机速度
//        m_enemys[i].m_Speed = ENEMY_SPEED;

//        //敌机矩形
//        m_enemys[i].m_Rect.setWidth(m_enemy.width());
//        m_enemys[i].m_Rect.setHeight(m_enemy.height());
//        m_enemys[i].m_Rect.moveTo(m_enemys[i].m_X,m_enemys[i].m_Y);
//    }

//    QPixmap m_Bullet;
//    m_Bullet.load(ENEMY_PATH);
//    /**********子弹属性更新***********/
//    for(int j = 0 ; j < BULLET_NUM;j++)
//    {
//        //加载子弹资源
//        m_hero.m_bullets[j].m_Bullet.load(BULLET_PATH);

//        //子弹坐标 初始坐标可随意设置，后期会重置
//        m_hero.m_bullets[j].m_X = GAME_WIDTH*0.5 - m_Bullet.width()*0.5;
//        m_hero.m_bullets[j].m_Y = GAME_HEIGHT;

//        //子弹状态
//        m_hero.m_bullets[j].m_Free = true;


//        //子弹矩形框
//        m_hero.m_bullets[j].m_Rect.setWidth(m_Bullet.width());
//        m_hero.m_bullets[j].m_Rect.setHeight(m_Bullet.height());
//        m_hero.m_bullets[j].m_Rect.moveTo(m_hero.m_bullets[j].m_X,m_hero.m_bullets[j].m_Y);
//    }
//}





