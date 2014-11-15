#ifndef DEMOCOQ_H
#define DEMOCOQ_H

#include <QObject>
#include "APIConnector.h"

class DemoCoq : public QObject
{
Q_OBJECT
public:
    struct KeyFrame {
        KeyFrame(float duration, QColor const& color);
        float   duration;
        QColor  color;
    };

    DemoCoq();

    void addAPIConnector(APIConnector *);

private slots:
    void    updateColor();

private:
    QList<APIConnector *>   _apis;
    QList<QList<KeyFrame>>  _frames;
    QTime   _anim;
};

#endif // DEMOCOQ_H
