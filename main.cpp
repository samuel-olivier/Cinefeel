#include "mainwindow.h"

#include <QApplication>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QLabel>
#include <QTimer>

#include <QDebug>
#include "democoq.h"
#include "videodebugger.h"

int             main(int argc, char *argv[])
{
    QApplication    a(argc, argv);
    QVideoWidget    *videoOutputWidget = new QVideoWidget();
    QMediaPlayer    *player = new QMediaPlayer();
    QVideoProbe     *probe = new QVideoProbe();
    DemoCoq*        demo = new DemoCoq();
    QTimer*         timer = new QTimer();

    probe->setSource(player);
    player->setMedia(QUrl::fromLocalFile("C:/Users/samuel/Documents/Dev/Cinefeel/Video.avi"));

    player->setVideoOutput(videoOutputWidget);

    videoOutputWidget->show();

    player->play();

    demo->connect(timer, SIGNAL(timeout()), SLOT(updateColor()));
    timer->start(1000 / 10);
    demo->addAPIConnector(new APIConnector("192.168.3.7:34000"));
//    demo->addAPIConnector(new APIConnector("192.168.43.254:34000"));
//    demo->addAPIConnector(new APIConnector("192.168.43.254:34000"));
//    demo->addAPIConnector(new APIConnector("192.168.43.254:34000"));
    //demo.launch();

    VideoDebugger   *videoDebugger = new VideoDebugger((QObject *)0, true);
    QObject::connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), videoDebugger, SLOT(mediaCheck(QMediaPlayer::MediaStatus)));
    QObject::connect(probe, SIGNAL(videoFrameProbed(QVideoFrame)), videoDebugger, SLOT(processFrame(QVideoFrame)));
    return a.exec();
}
