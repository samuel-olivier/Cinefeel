#include "APIConnector.h"

#include <QDebug>

APIConnector::APIConnector(QString const& host)
    : _networkManager(new QNetworkAccessManager())
{
    _templateRequest.setRawHeader("User-Agent", "CineFeelBrowser 1.0");
    _templateRequest.setRawHeader("Content-Type", "application/json");
    _host = host;
}

APIConnector::~APIConnector()
{
    delete _networkManager;
}

void APIConnector::setHost(const QString &ip)
{
    _host = ip;
}

void APIConnector::setColor(const QColor &color)
{
    _postRequest("Light/Capability/ColorLight/Rgb.json?red=" + QString::number(color.red()) +
                 "&green=" + QString::number(color.green()) +
                 "&blue=" + QString::number(color.blue()));
}

void APIConnector::setBrightness(int brightness)
{
    _postRequest("Light/Capability/WhiteLight.json?brightness=" + QString::number(brightness));
}

void APIConnector::setTemperature(int temperature)
{
    _postRequest("Light/Capability/WhiteLight.json?temperature=" + QString::number(temperature));
}

void APIConnector::_postRequest(const QString &path)
{
    _templateRequest.setUrl(QUrl("http://" + _host + "/" + path));
    _networkManager->put(_templateRequest, QByteArray());
}
