#ifndef APICONNECTOR_H
#define APICONNECTOR_H

#include <QColor>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class APIConnector
{
public:
    APIConnector();
    ~APIConnector();

    void    setHost(QString const& ip);

    void    setColor(QColor const& color);
    void    setBrightness(int brightness);
    void    setTemperature(int temperature);

private:
    void    _postRequest(QString const& path);

    QNetworkAccessManager*  _networkManager;
    QNetworkRequest         _templateRequest;
    QString                 _host;
};

#endif // APICONNECTOR_H
