#ifndef VIDEODEBUGGER_H
#define VIDEODEBUGGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QVideoFrame>
#include <QDebug>

#include <QLabel>
#include <QPalette>

#include "APIConnector.h"

class VideoDebugger : public QObject
{
    Q_OBJECT
public:
    explicit VideoDebugger(QObject *parent = 0);

signals:

public slots:
    void        mediaCheck(QMediaPlayer::MediaStatus status);
    void        processFrame(QVideoFrame frame);

private:
    QLabel      *_label;
    QPalette    _pal;
    APIConnector    *_API;

};

#endif // VIDEODEBUGGER_H
