#include "Headers/requesthandler.h"

RequestHandler::RequestHandler(QObject *parent)
    : QObject(parent)
{
    network_manager = new QNetworkAccessManager(this);
    base_url = "http://127.0.0.1:8080";
    connect(network_manager, &QNetworkAccessManager::finished, this, &RequestHandler::onReplyFinished);
    endpoints.insert(QString("/getInfo"), handleGetInfoReply);
    endpoints.insert(QString("/getModes"), handleGetModesReply);
    endpoints.insert(QString("/selectMode"), handleSelectModeReply);
    endpoints.insert(QString("/setBrightness"), handleSetBrightnessReply);
    endpoints.insert(QString("/setState"), handleSetStateReply);
    endpoints.insert(QString("/setModeParameter"), handleSetModeParameterReply);
}
void RequestHandler::getInfo()
{
    QUrl url(base_url + "/getInfo");
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::getModes()
{
    QUrl url(base_url + "/getModes");
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::selectMode(QString mode_id)
{
    QUrl url(base_url + "/selectMode");
    QUrlQuery query;
    query.addQueryItem("mode_id", mode_id);
    url.setQuery(query);
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::setBrightness(QString brightness)
{
    QUrl url(base_url + "/setBrightness");
    QUrlQuery query;
    query.addQueryItem("brightness", brightness);
    url.setQuery(query);
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::setState(QString state)
{
    QUrl url(base_url + "/setState");
    QUrlQuery query;
    query.addQueryItem("state", state);
    url.setQuery(query);
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::setModeColor(QString hex)
{
    QUrl url(base_url + "/setModeParameter");
    QUrlQuery query;
    query.addQueryItem("parameter_name", "color");
    query.addQueryItem("value", hex);
    url.setQuery(query);
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::onReplyFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if(endpoints.find(url.path()) != endpoints.end())
    {
        (this->*endpoints[url.path()])(reply);
    }
    reply->deleteLater();
}
void RequestHandler::handleGetModesReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonArray modesArray = jsonDoc.array();
        QVariantList modes;
        for (const QJsonValue &value : modesArray)
        {
            modes.append(value);
        }
        emit modesReceived(modes);
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
}
void RequestHandler::handleSelectModeReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        emit modeSelected(true);
        qDebug() << "Mode selected successfully.";
    }
    else
    {
        emit modeSelected(false);
        qDebug() << "Failed to select mode:" << reply->errorString();
    }
}
void RequestHandler::handleGetInfoReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject obj = jsonDoc.object();
        emit infoReceived(obj);
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
}
void RequestHandler::handleSetBrightnessReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Brigthness set";
    }
    else
    {
        qDebug() << "Failed to set brigthness:" << reply->errorString();
    }
}
void RequestHandler::handleSetStateReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "State set";
    }
    else
    {
        qDebug() << "Failed to set state:" << reply->errorString();
    }
}
void RequestHandler::handleSetModeParameterReply(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Parameter set";
    }
    else
    {
        qDebug() << "Failed to set parameter:" << reply->errorString();
    }
}
