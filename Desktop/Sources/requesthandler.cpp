#include "Headers/requesthandler.h"

RequestHandler::RequestHandler(QObject *parent)
    : QObject(parent)
{
    network_manager = new QNetworkAccessManager(this);
    base_url = "http://127.0.0.1:8080";
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
    endpoints.insert("/mode", [this](QNetworkReply* reply)
        {
            if (reply->operation() == QNetworkAccessManager::GetOperation)
            {
                handleSetModeParameter(reply);
            }
            else if (reply->operation() == QNetworkAccessManager::PostOperation)
            {
                handleAddMode(reply);
            }
            else if (reply->operation() == QNetworkAccessManager::DeleteOperation)
            {
                handleDeleteMode(reply);
            }
        });
}
void RequestHandler::onReplyFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if(endpoints.find(url.path()) != endpoints.end())
    {
        //(this->*endpoints[url.path()])(reply);
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
void RequestHandler::addMode(QJsonObject mode)
{

}
void RequestHandler::deleteMode()
{
    QUrl url(base_url + "/mode");
    QNetworkRequest request(url);
    network_manager->deleteResource(request);
}
void RequestHandler::setModeParameter(QString parameter_name, QString value)
{
    QUrl url(base_url + "/mode");
    QUrlQuery query;
    query.addQueryItem(parameter_name, value);
    url.setQuery(query);
    QNetworkRequest request(url);
    network_manager->get(request);
}

void RequestHandler::handleGetSettings(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject obj = jsonDoc.object();
        emit settingsReceived(obj);
    }
    else
    {
        qDebug() << "Failer receive settings:" << reply->errorString();
    }
}
void RequestHandler::handleSetSettings(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Settings parameter set";
    }
    else
    {
        qDebug() << "Failed to set parameter:" << reply->errorString();
    }
}
void RequestHandler::handleGetModes(QNetworkReply *reply)
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
void RequestHandler::handleAddMode(QNetworkReply* reply)
{

}
void RequestHandler::handleDeleteMode(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "Mode deleted";
        getModes();
        getSettings();
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
}
void RequestHandler::handleSetModeParameter(QNetworkReply* reply)
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
