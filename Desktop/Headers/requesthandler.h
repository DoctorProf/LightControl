#pragma once

#include "networkutils.h"
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QMap>
#include <functional>

class RequestHandler;
using handler = std::function<void(QNetworkReply*)>;

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    RequestHandler(QObject *parent = nullptr);
    Q_INVOKABLE void getSettings();
    Q_INVOKABLE void setSettings(QString parameter_name, QString value);
    Q_INVOKABLE void getModes();
    Q_INVOKABLE void getModeParams();
    Q_INVOKABLE void setModeParams(QString parameter_name, QString internal_param, QString value);

private slots:
    void onReplyFinished(QNetworkReply* reply);
signals:
    void settingsReceived(QJsonObject obj);
    void modesReceived(QJsonObject modes);
    void paramsModeReceived(QJsonObject params);
    void responseMessage(QString message);
private:
    QNetworkAccessManager* network_manager;
    QString base_url;
    QMap<QString, handler> endpoints;

    void handleGetSettings(QNetworkReply* reply);
    void handleSetSettings(QNetworkReply* reply);
    void handleGetModes(QNetworkReply* reply);
    void handleGetModeParams(QNetworkReply* reply);
    void handleSetModeParams(QNetworkReply* reply);
};
