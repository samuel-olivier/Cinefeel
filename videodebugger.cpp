#include "videodebugger.h"
#include <QColor>

VideoDebugger::VideoDebugger(QObject *parent) :
    QObject(parent),
    _label(new QLabel()),
    _pal(_label->palette()),
    _API(new APIConnector())
{
    this->_label->setFixedSize(QSize(200, 200));
    this->_label->show();
    this->_API->setHost("192.168.3.7:34000");
}

void
VideoDebugger::mediaCheck(QMediaPlayer::MediaStatus status) {
    qDebug() << status;
}

void
VideoDebugger::processFrame(QVideoFrame frame)
{
    if (frame.map(QAbstractVideoBuffer::ReadOnly) == true)
    {
        if (frame.isReadable() == true)
        {
            QColor    color;
            uchar *bits = frame.bits();

            float Y, U, V;
            float R = 0.0, G = 0.0, B = 0.0;

            int sampleNumber = 0;
            for (int x = 0 ; x < frame.width() ; x += 10) {
                for (int y = 0 ; y < frame.height() ; y += 10) {
                    sampleNumber++;

                    Y = bits[x + y * frame.width()];
                    U = bits[frame.width() * frame.height() + (x + y * frame.width()) / 4] - 128;
                    V = bits[frame.width() * frame.height() + frame.width() * frame.height() / 4 + (x + y * frame.width()) / 4] - 128;


                    R += (Y + 1.13983 * V) / 255;
                    G += (Y - 0.39465 * U - 0.58060 * V) / 255;
                    B += (Y + 2.03211 * U) / 255;


                }
            }
            color.setRedF(R / sampleNumber);
            color.setGreenF(G / sampleNumber);
            color.setBlueF(B / sampleNumber);

            this->_API->setColor(color);
//            qDebug() << color;

            this->_pal.setColor(this->_label->backgroundRole(), color);
            this->_label->setPalette(this->_pal);

        }
        frame.unmap();
    }
}
