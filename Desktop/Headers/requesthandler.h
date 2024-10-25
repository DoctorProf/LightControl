#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>
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
    Q_INVOKABLE void addMode(QJsonObject mode);
    Q_INVOKABLE void deleteMode();
    Q_INVOKABLE void setModeParameter(QString parameter_name, QString value);

private slots:
    void onReplyFinished(QNetworkReply* reply);
signals:
    void settingsReceived(QJsonObject obj);
    void modesReceived(QVariantList modes);
    void modeSelected(bool success);

private:
    QNetworkAccessManager* network_manager;
    QString base_url;
    QMap<QString, handler> endpoints;

    void handleGetSettings(QNetworkReply* reply);
    void handleSetSettings(QNetworkReply* reply);
    void handleGetModes(QNetworkReply* reply);
    void handleAddMode(QNetworkReply* reply);
    void handleDeleteMode(QNetworkReply* reply);
    void handleSetModeParameter(QNetworkReply* reply);
};
