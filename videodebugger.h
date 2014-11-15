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
#include "ui_form.h"

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
    Ui_Colors           *_colorsWindow;
    APIConnector        *_API;
    QList<QMap<Color*, int>>      map;
    QList<Color*>           _palet;
    QList<QTime>                 _timer;
    QList<QList<QColor>>        _lastColors;
    QList<QColor>               _average;
    bool               _display;
};

#endif // VIDEODEBUGGER_H
