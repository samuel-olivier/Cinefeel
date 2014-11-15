#include "mainwindow.h"

#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QLabel>

#include <QDebug>
#include "videodebugger.h"

int             main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    QVideoWidget    *videoOutputWidget = new QVideoWidget();
    QMediaPlayer    *player = new QMediaPlayer();
    QVideoProbe     *probe = new QVideoProbe();

    probe->setSource(player);
    player->setMedia(QUrl::fromLocalFile("C:/Users/louis/Documents/cinefeel/VIDEOBRESS-final.mp4"));

    player->setVideoOutput(videoOutputWidget);

    videoOutputWidget->show();

    player->play();

    VideoDebugger   *videoDebugger = new VideoDebugger();
    QObject::connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), videoDebugger, SLOT(mediaCheck(QMediaPlayer::MediaStatus)));
    QObject::connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)), videoDebugger, SLOT(processFrame(QVideoFrame)));
    return a.exec();
}
