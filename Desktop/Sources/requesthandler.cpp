#include "Headers/requesthandler.h"

RequestHandler::RequestHandler(QObject *parent)
    : QObject(parent)
{
    network_manager = new QNetworkAccessManager(this);
    base_url = "http://127.0.0.1:5000";
    connect(network_manager, &QNetworkAccessManager::finished, this, &RequestHandler::onReplyFinished);
    endpoints.insert(QString("/getSettings"), [this](QNetworkReply* reply)
    {
        if (reply->operation() == QNetworkAccessManager::GetOperation)
        {
            handleGetSettings(reply);
        }
    });
    endpoints.insert(QString("/setSettings"), [this](QNetworkReply* reply)
    {
        if (reply->operation() == QNetworkAccessManager::GetOperation)
        {
            handleSetSettings(reply);
        }
    });
    endpoints.insert(QString("/modes"), [this](QNetworkReply* reply)
    {
        if (reply->operation() == QNetworkAccessManager::GetOperation)
        {
            handleGetModes(reply);
        }
    });
    endpoints.insert(QString("/getModeParams"), [this](QNetworkReply* reply)
    {
        if (reply->operation() == QNetworkAccessManager::GetOperation)
        {
            handleGetModeParams(reply);
        }
    });
    endpoints.insert(QString("/setModeParams"), [this](QNetworkReply* reply)
    {
        if (reply->operation() == QNetworkAccessManager::GetOperation)
        {
            handleSetModeParams(reply);
        }
    });
}
void RequestHandler::onReplyFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if(endpoints.find(url.path()) != endpoints.end())
    {
        endpoints[url.path()](reply);
    }
    reply->deleteLater();
}

void RequestHandler::getSettings()
{
    QUrl url(base_url + "/getSettings");
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::setSettings(QString parameter_name, QString value)
{
    QUrl url(base_url + "/setSettings");
    QUrlQuery query;
    query.addQueryItem(parameter_name, value);
    url.setQuery(query);
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::getModes()
{
    QUrl url(base_url + "/modes");
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::getModeParams()
{
    QUrl url(base_url + "/getModeParams");
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::setModeParams(QString parameter_name, QString internal_param, QString value)
{
    QUrl url(base_url + "/setModeParams");
    QUrlQuery query;
    query.addQueryItem("parameter_name", parameter_name);
    query.addQueryItem(internal_param, value);
    url.setQuery(query);
    QNetworkRequest request(url);
    network_manager->get(request);
}
void RequestHandler::handleGetSettings(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        emit settingsReceived(network_utils::extractJsonObj(reply));
        emit responseMessage(network_utils::extractResponseMessage(reply));
    }
}
void RequestHandler::handleSetSettings(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        emit responseMessage(network_utils::extractResponseMessage(reply));
    }
}
void RequestHandler::handleGetModes(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        emit modesReceived(network_utils::extractJsonObj(reply));
        emit responseMessage(network_utils::extractResponseMessage(reply));
    }
}
void RequestHandler::handleGetModeParams(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        emit paramsModeReceived(network_utils::extractJsonObj(reply));
        emit responseMessage(network_utils::extractResponseMessage(reply));
    }
}
void RequestHandler::handleSetModeParams(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        emit responseMessage(network_utils::extractResponseMessage(reply));
    }
}
