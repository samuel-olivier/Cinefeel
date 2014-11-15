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

    int divisions = 4;
    for (int r = 0; r < divisions; ++r) {
        for (int g = 0; g < divisions; ++g) {
            for (int b = 0; b < divisions; ++b) {
                Color* color = new Color();
                color->red = r * 255 / (divisions - 1);
                color->green = g * 255 / (divisions - 1);
                color->blue = b * 255 / (divisions - 1);

                _palet.append(color);
            }
        }
    }
}

void
VideoDebugger::mediaCheck(QMediaPlayer::MediaStatus status) {
    qDebug() << status;
}

float
VideoDebugger::clamp(float value)
{
    return value < 0.0 ? 0.0 : (value > 255.0 ? 255.0 : value);
}
int count = 0;
void
VideoDebugger::processFrame(QVideoFrame frame)
{
    if (frame.map(QAbstractVideoBuffer::ReadOnly) == true)
    {
        qDebug() << frame.pixelFormat();
        if (frame.isReadable() == true)
        {
            count++;

            this->map.clear();
            uchar *bits = frame.bits();
            float Y, U, V;
            float R, G, B;

            int incrX = 0;
            int incrY = 0;

            if (count == 500) {
                QImage image(frame.width(), frame.height(), QImage::Format_RGB32);
                for (int y = 0 ; y < frame.width() ; y += 1) {
                    for (int x = 0, incrX = 0 ; x < frame.height() ; x += 1) {/*
                       const int xx = x >> 1;
                       const int yy = y >> 1;
                       const int Y = frame.data[0][y * frame.linesize[0] + x] - 16;
                       const int U = frame.data[1][yy * frame.linesize[1] + xx] - 128;
                       const int V = frame.data[2][yy * frame.linesize[2] + xx] - 128;
                       const int r = qBound(0, (298 * Y           + 409 * V + 128) >> 8, 255);
                       const int g = qBound(0, (298 * Y - 100 * U - 208 * V + 128) >> 8, 255);
                       const int b = qBound(0, (298 * Y + 516 * U           + 128) >> 8, 255);*/

                        Y = bits[x + y * frame.width()];

                        if (x % 4 == 0)
                            incrX += 1;
                        if (y % 4 == 0)
                            incrY += 1;

                        U = bits[frame.width() * frame.height() + (incrX + incrY * frame.width()) + 0] - 128;
                        V = bits[frame.width() * frame.height() + (incrX + incrY * frame.width()) + 1] - 128;

 //                       V = bits[frame.width() * frame.height() + frame.width() * frame.height() / 4 + (x + y * frame.width()) / 4] - 128;


                        /*B = this->clamp(1.164*(Y - 16) + 2.018*(U - 128));
                        G = this->clamp(1.164*(Y - 16) - 0.813*(V - 128) - 0.391*(U - 128));
                        R = this->clamp(1.164*(Y - 16) + 1.596*(V - 128));*/

//                        R = 1.164 * (Y-16) + 1.596*(V - 128);
//                        G = 1.164 * (Y-16) - 0.813 * (V - 128) - 0.391 * (U - 128);
//                        B = 1.164 * (Y-16) + 2.018 * (U - 128);

                        R = Y + 1.402 * V;
                        G = Y - 0.34414 * U - 0.71414 * V;
                        B = Y + 1.772 * U;

//                        R = Y + 1.402 * (V - 128);
//                        G = Y - 0.34414 * (Y - 128) - 0.71414 * (V - 128);
//                        B = Y + 1.772 * (U - 128);

//                        R = this->clamp(Y + 1.13983 * V);
//                        G = this->clamp(Y - 0.39465 * U - 0.58060 * V);
//                        B = this->clamp(Y + 2.03211 * U);

                        image.setPixel(x, y, QColor(R, G, B).rgb());
                    }
                }
                image.save("C:/Users/louis/Documents/Rendu/test.png");
            }

            QColor    color;

            int sampleNumber = 0;
            for (int x = 0 ; x < frame.width() ; x += 20) {
                for (int y = 0 ; y < frame.height() ; y += 20) {
                    sampleNumber++;

                    Y = bits[x + y * frame.width()];
                    U = bits[frame.width() * frame.height() + (x + y * frame.width()) / 4] - 128;
                    V = bits[frame.width() * frame.height() + frame.width() * frame.height() / 4 + (x + y * frame.width()) / 4] - 128;

                    /*
                    B = this->clamp(1.164*(Y - 16) + 2.018*(U - 128));
                    G = this->clamp(1.164*(Y - 16) - 0.813*(V - 128) - 0.391*(U - 128));
                    R = this->clamp(1.164*(Y - 16) + 1.596*(V - 128));*/
                    R = this->clamp(Y + 1.13983 * V);
                    G = this->clamp(Y - 0.39465 * U - 0.58060 * V);
                    B = this->clamp(Y + 2.03211 * U);

                    if (R >= 0 && G >= 0 && B >= 0 ) {
                        int min = -1;
                        Color* best = NULL;
                        for (Color* color : _palet) {
                            int dist = color->distance(R, G, B);
                            if (min == -1 || dist < min) {
                                min = dist;
                                best = color;
                            }
                        }
                        if (best) {
                            if (map.contains(best)) {
                                map[best] += 1;
                            } else {
                                map[best] = 1;
                            }
                        }
                    }
                }
            }

            int count = 0;
            int frequentColor;

            for (QMap<Color*, int>::iterator it = map.begin(); it != map.end(); ++it) {
                if (it.value() > count) {
                    count = it.value();


                    color.setRed(it.key()->red);
                    color.setGreen(it.key()->green);
                    color.setBlue(it.key()->blue);

                }
            }

            qDebug() << color;

            this->_API->setColor(color);

            this->_pal.setColor(this->_label->backgroundRole(), color);
            this->_label->setPalette(this->_pal);

        }
        frame.unmap();
    }
}
