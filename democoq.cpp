#include "democoq.h"

#include <QDebug>

typedef struct s_demo
{
    int bulb;
    QColor color;
    float timer;
}              t_demo;

t_demo demo[]=
{
    {0, QColor(255, 0, 0), 0.5f},
    {1, QColor(255, 0, 0), 0.5f},
    {2, QColor(255, 0, 0), 0.5f},
    {3, QColor(255, 0, 0), 0.5f},
    {0, QColor(0, 255, 0), 0.5f},
    {1, QColor(0, 255, 0), 0.5f},
    {2, QColor(0, 255, 0), 0.5f},
    {3, QColor(0, 255, 0), 0.5f},
    {0, QColor(0, 0, 255), 0.5f},
    {1, QColor(0, 0, 255), 0.5f},
    {2, QColor(0, 0, 255), 0.5f},
    {3, QColor(0, 0, 255), 0.5f},
    {-1, QColor(0, 0, 0), 0.5f}
};

DemoCoq::DemoCoq() : QObject(NULL)
{
    this->_anim.restart();
    QList<KeyFrame> anim1;
    anim1 << KeyFrame(3, QColor(255, 0, 0))
          << KeyFrame(3, QColor(0, 255, 0))
          << KeyFrame(3, QColor(0, 0, 255));
    QList<KeyFrame> anim2;
    anim2 << KeyFrame(3, QColor(0, 255, 0))
          << KeyFrame(3, QColor(0, 0, 255))
          << KeyFrame(3, QColor(255, 0, 0));
    QList<KeyFrame> anim3;
    anim3 << KeyFrame(3, QColor(0, 0, 255))
          << KeyFrame(3, QColor(255, 0, 0))
          << KeyFrame(3, QColor(0, 255, 0));
    QList<KeyFrame> anim4;
    anim4 << KeyFrame(3, QColor(255, 255, 0))
          << KeyFrame(3, QColor(0, 255, 255))
          << KeyFrame(3, QColor(255, 0, 255));
    this->_frames << anim1 << anim2 << anim3 << anim4;
}

void DemoCoq::addAPIConnector(APIConnector *api)
{
    this->_apis.append(api);
}

void DemoCoq::updateColor()
{
    auto it = this->_frames.begin();
    float time = float(this->_anim.elapsed()) / 1000;
    for (auto itAPI : this->_apis) {
        float incr = 0;
        QColor color(0, 0, 0);
        for (auto itFrames : *it) {
            if (time >= incr && time < incr + itFrames.duration) {
                color = itFrames.color;
                break;
            }
            incr += itFrames.duration;
        }
        itAPI->setColor(color);
        qDebug() << color << time;
        ++it;
    }
}


DemoCoq::KeyFrame::KeyFrame(float duration, const QColor &color)
{
    this->duration = duration;
    this->color = color;
}
