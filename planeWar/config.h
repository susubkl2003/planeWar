#ifndef CONFIG_H
#define CONFIG_H

#endif // CONFIG_H


/**********  游戏配置数据 **********/
#define GAME_WIDTH  480  //宽度
#define GAME_HEIGHT 690  //高度
#define GAME_TITLE "飞机大战 MADE IN SUSU" //标题
//#define GAME_RES_PATH  "./plane.rcc" //rcc文件路径
#define GAME_ICON ":/res/enemy1.png"//图标文件
#define GAME_RATE  10   //刷新间隔，帧率 单位毫秒
#define GAME_LIFE  3   //生命值
#define GAME_LIFE_JUMP_COUNT 100  //生命值闪烁次数
#define GAME_LIFE_JUMP_SPACE 8 //生命值闪烁间隔
#define LIFE_PATH  ":/res/life_%1.png"

/**********  地图配置数据 **********/
#define MAP_PATH  ":/res/background.png" //地图图片路径
#define MAP_SCROLL_SPEED 2  //地图滚动速度

/**********  飞机配置数据 **********/
#define HERO_PATH ":/res/me1.png"
#define HERO_PATH_2 ":/res/me2.png"

/**********  子弹配置数据 **********/
#define BULLET_PATH ":/res/bullet2.png"   //子弹图片路径
#define BULLET_SPEED 5  //子弹移动速度
#define BULLET_NUM 30   //弹匣中子弹总数
#define BULLET_INTERVAL 20 //发射子弹时间间隔

/**********  敌机配置数据 **********/
#define ENEMY_PATH  ":/res/enemy2.png"  //敌机资源图片
#define ENEMY_SPEED 5  //敌机移动速度
#define ENEMY_NUM   20  //敌机总数量
#define ENEMY_INTERVAL  30  //敌机出场时间间隔

/**********  爆炸配置数据 **********/
#define BOMB_PATH  ":/res/enemy2_down%1.png"   //爆炸资源图片
#define BOMB_NUM  20     //爆炸数量
#define BOMB_MAX  4      //爆炸图片最大索引
#define BOMB_INTERVAL 20   //爆炸切图时间间隔

/**********  音效配置数据 **********/
#define SOUND_BACKGROUND_2 "qrc:/music/game_music.wav"
#define SOUND_BOMB "qrc:/music/enemy1_down.wav"
#define SOUND_MAX 10



