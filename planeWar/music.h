#ifndef MUSIC_H
#define MUSIC_H
#include <QThread>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QUrl>
#include "config.h"
class Music:public QThread
{
public:
    Music();
//public slots:
//    void playMusic()
//    {
//        //启动背景音乐
//        //先new一个output对象
//        auto audioOutput=new QAudioOutput(this);
//        //再来一个媒体播放器对象
//        auto mediaPlayer=new QMediaPlayer(this);
//        mediaPlayer->setAudioOutput(audioOutput);
//        //给播放器设置音乐
//        mediaPlayer->setSource(
//            QUrl(SOUND_BACKGROUND_2));
//        mediaPlayer->play();
//    }
protected:
    void run();

};

#endif // MUSIC_H
