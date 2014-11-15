#include "videodebugger.h"
#include <QColor>

VideoDebugger::VideoDebugger(QObject *parent, bool display) :
    QObject(parent),
    _colorsWindow(new Ui_Colors()),
    _display(display),
    _API(new APIConnector("192.168.3.7:34000"))
{
    for (int i = 0; i < 4; ++i) {
        QMap<Color*, int> m;
        map.append(m);
        QColor c = QColor(0, 0, 0);
        _average.append(c);
        QList<QColor> lc;
        _lastColors.append(lc);
        QTime t;
        _timer.append(t);
        this->_timer[i].restart();
    }
    QWidget* wid = new QWidget(0);
    _colorsWindow->setupUi(wid);
    wid->show();
    this->_API->setHost("192.168.43.170:34000");

    int divisions = 10;
    for (int r = 2; r < divisions; ++r) {
        for (int g = 2; g < divisions; ++g) {
            for (int b = 2; b < divisions; ++b) {
                Color* color = new Color();
                color->red = r * 255 / (divisions - 1);
                color->green = g * 255 / (divisions - 1);
                color->blue = b * 255 / (divisions - 1);

                if (qAbs(r - b) > 0 || qAbs(r - g) > 0)
                    _palet.append(color);
            }
        }
    }

    this->_colorsWindow->label_1->setAutoFillBackground(true);
    this->_colorsWindow->label_2->setAutoFillBackground(true);
    this->_colorsWindow->label_3->setAutoFillBackground(true);
    this->_colorsWindow->label_4->setAutoFillBackground(true);

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
        //qDebug() << frame.pixelFormat();
        if (frame.isReadable() == true)
        {
            count++;

            for (int i = 0; i < 4; ++i) {
                this->map[i].clear();
                for (Color* color : _palet) {
                    this->map[i][color] = 0;
                }
            }
            uchar *bits = frame.bits();
            float Y, U, V;
            float R, G, B;

            if (false && count == 200) {
                QImage image(frame.width(), frame.height(), QImage::Format_RGB32);
                for (int x = 0 ; x < frame.width() ; x += 1) {
                    for (int y = 0 ; y < frame.height() ; y += 1) {/*
                       const int xx = x >> 1;
                       const int yy = y >> 1;
                       const int Y = frame.data[0][y * frame.linesize[0] + x] - 16;
                       const int U = frame.data[1][yy * frame.linesize[1] + xx] - 128;
                       const int V = frame.data[2][yy * frame.linesize[2] + xx] - 128;
                       const int r = qBound(0, (298 * Y           + 409 * V + 128) >> 8, 255);
                       const int g = qBound(0, (298 * Y - 100 * U - 208 * V + 128) >> 8, 255);
                       const int b = qBound(0, (298 * Y + 516 * U           + 128) >> 8, 255);*/



                        Y = bits[x + y * frame.width()];
                        U = bits[frame.width() * frame.height() + 2 * (x / 2 + (y / 2) * (frame.width() / 2))];
                        V = bits[frame.width() * frame.height() + 2 * ((x / 2 + (y / 2) * (frame.width() / 2))) + 1];


 //                       V = bits[frame.width() * frame.height() + frame.width() * frame.height() / 4 + (x + y * frame.width()) / 4] - 128;


//                        R = this->clamp(1.164*(Y - 16) + 1.596*(V - 128));
//                        G = this->clamp(1.164*(Y - 16) - 0.813*(V - 128) - 0.391*(U - 128));
//                        B = this->clamp(1.164*(Y - 16) + 2.018*(U - 128));

//                        R = 1.164 * (Y-16) + 1.596*(V - 128);
//                        G = 1.164 * (Y-16) - 0.813 * (V - 128) - 0.391 * (U - 128);
//                        B = 1.164 * (Y-16) + 2.018 * (U - 128);

//                        R = Y + 1.402 * V;
//                        G = Y - 0.34414 * U - 0.71414 * V;
//                        B = Y + 1.772 * U;

//                        R = Y + 1.402 * (V - 128);
//                        G = Y - 0.34414 * (Y - 128) - 0.71414 * (V - 128);
//                        B = Y + 1.772 * (U - 128);

//                        R = this->clamp(Y + V * 1.13983);
//                        G = this->clamp(Y - 0.39465 * U - 0.58060 * V);
//                        B = this->clamp(Y + 2.03211 * U);

                        R = Y + 1.4075 * (V - 128);
                        G = Y - 0.3455 * (U - 128) - (0.7169 * (V - 128));
                        B = Y + 1.7790 * (U - 128);

                        //qDebug() << Y << U << V << R << G << B;

                        image.setPixel(x, y, QColor(R, G, B).rgb());
                    }
                }
                image.save("C:/Users/louis/Documents/Rendu/test.png");
            }


            int sampleNumber = 0;
            for (int x = 0 ; x < frame.width() ; x += 20) {
                for (int y = 0 ; y < frame.height() ; y += 20) {
                    sampleNumber++;

                    Y = bits[x + y * frame.width()];
                    U = bits[frame.width() * frame.height() + 2 * (x / 2 + (y / 2) * (frame.width() / 2))];
                    V = bits[frame.width() * frame.height() + 2 * ((x / 2 + (y / 2) * (frame.width() / 2))) + 1];

                    R = Y + 1.4075 * (V - 128);
                    G = Y - 0.3455 * (U - 128) - (0.7169 * (V - 128));
                    B = Y + 1.7790 * (U - 128);

                    if (R >= 30 && G >= 30 && B >= 30 && (qAbs(R - G) > 30 || qAbs(R - B) > 30)) {
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
                            if (x < frame.width() / 2 && y < frame.height() / 2) {
                                map[0][best] += 1;
                            }
                            else if (x >= frame.width() / 2 && y < frame.height() / 2) {
                                map[1][best] += 1;
                            }
                            else if (x < frame.width() / 2 && y >= frame.height() / 2) {
                                map[2][best] += 1;
                            }
                            else {
                                map[3][best] += 1;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < 4; ++i) {
                QColor    color;
                int count = 0;
                for (QMap<Color*, int>::iterator it = map[i].begin(); it != map[i].end(); ++it) {
                    if (it.value() > count) {
                        count = it.value();


                        color.setRed(it.key()->red);
                        color.setGreen(it.key()->green);
                        color.setBlue(it.key()->blue);

                    }
                }

                this->_lastColors[i].push_back(color);
                int size = this->_lastColors[i].size();

                if (size > 5) {
                    this->_average[i].setRed(clamp((this->_average[i].red() * (size - 1) - this->_lastColors[i].first().red() + color.red()) / (size - 1)));
                    this->_average[i].setGreen(clamp((this->_average[i].green() * (size - 1) - this->_lastColors[i].first().green() + color.green()) / (size - 1)));
                    this->_average[i].setBlue(clamp((this->_average[i].blue() * (size - 1) - this->_lastColors[i].first().blue() + color.blue()) / (size - 1)));
                    this->_lastColors[i].removeFirst();
                } else if (size == 1) {
                    this->_average[i] = color;
                } else {
                    this->_average[i].setRed((this->_average[i].red() * (size - 1) + color.red()) / size);
                    this->_average[i].setGreen((this->_average[i].green() * (size - 1) + color.green()) / size);
                    this->_average[i].setBlue((this->_average[i].blue() * (size - 1) + color.blue()) / size);
                }

                Color c;
                c.red = color.red();
                c.green= color.green();
                c.blue = color.blue();
                if (this->_timer[i].elapsed() > 1000 / 10 || c.distance(_average[i].red(), _average[i].green(), _average[i].blue()) > 120) {
                    this->_API->setColor(_average[i]);
                    QPalette palette;
                    if (i == 0) {
                        palette.setColor(this->_colorsWindow->label_1->backgroundRole(), _average[i]);
                        palette.setColor(this->_colorsWindow->label_1->foregroundRole(), _average[i]);
                        this->_colorsWindow->label_1->setPalette(palette);
                    } else if (i == 1) {
                        palette.setColor(this->_colorsWindow->label_2->backgroundRole(), _average[i]);
                        palette.setColor(this->_colorsWindow->label_2->foregroundRole(), _average[i]);
                        this->_colorsWindow->label_2->setPalette(palette);
                    } else if (i == 2) {
                        palette.setColor(this->_colorsWindow->label_3->backgroundRole(), _average[i]);
                        palette.setColor(this->_colorsWindow->label_3->foregroundRole(), _average[i]);
                        this->_colorsWindow->label_3->setPalette(palette);
                    } else {
                        palette.setColor(this->_colorsWindow->label_4->backgroundRole(), _average[i]);
                        palette.setColor(this->_colorsWindow->label_4->foregroundRole(), _average[i]);
                        this->_colorsWindow->label_4->setPalette(palette);
                    }
                    this->_timer[i].restart();
                }
            }
        }
        frame.unmap();
    }
}
