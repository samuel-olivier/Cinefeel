#ifndef VIDEODEBUGGER_H
#define VIDEODEBUGGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QVideoFrame>
#include <QDebug>
#include <QMap>
#include <QColor>
#include <QPair>
#include <QTime>
#include <QLabel>
#include <QPalette>

#include "APIConnector.h"
#include "color.h"

class VideoDebugger : public QObject
{
    Q_OBJECT
public:
    explicit VideoDebugger(QObject *parent = 0, bool display = true);

signals:

public slots:
    void        mediaCheck(QMediaPlayer::MediaStatus status);
    void        processFrame(QVideoFrame frame);
    float        clamp(float);

private:
    QLabel              *_label;
    QPalette            _pal;
    APIConnector        *_API;
    QMap<Color*, int>      map;
    QList<Color*>           _palet;
    bool               _display;
    QTime               _timer;
    QList<QColor>        _lastColors;
    QColor               _average;
};

#endif // VIDEODEBUGGER_H
