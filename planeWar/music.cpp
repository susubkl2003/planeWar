#include "music.h"

Music::Music()
{

}

void Music::run()
{
    //启动背景音乐
    //先new一个output对象
    auto audioOutput=new QAudioOutput(this);
    audioOutput->setVolume(0.5);
    //再来一个媒体播放器对象
    auto mediaPlayer=new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);
    //给播放器设置音乐
    mediaPlayer->setSource(
        QUrl(SOUND_BACKGROUND_2));
    mediaPlayer->setLoops(-1);
    mediaPlayer->play();
}
