#pragma once

#include "networkutils.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QMap>
#include <functional>

//template <typename... Args>
class RequestHandler;
//using handler = void (RequestHandler::*)(QNetworkReply*);
using handler = std::function<void(QNetworkReply*)>;

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    RequestHandler(QObject *parent = nullptr);
    Q_INVOKABLE void getSettings();
    Q_INVOKABLE void setSettings(QString parameter_name, QString value);
    Q_INVOKABLE void getModes();

private slots:
    void onReplyFinished(QNetworkReply* reply);
signals:
    void settingsReceived(QJsonObject obj);
    void modesReceived(QJsonObject modes);
    void responseMessage(QString message);
private:
    QNetworkAccessManager* network_manager;
    QString base_url;
    QMap<QString, handler> endpoints;

    void handleGetSettings(QNetworkReply* reply);
    void handleSetSettings(QNetworkReply* reply);
    void handleGetModes(QNetworkReply* reply);
};
