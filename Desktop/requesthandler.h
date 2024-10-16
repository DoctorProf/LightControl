#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>
#include <QUrlQuery>

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    RequestHandler(QObject *parent = nullptr);
    Q_INVOKABLE void getInfo();
    Q_INVOKABLE void getModes();
    Q_INVOKABLE void selectMode(QString mode_id);
    Q_INVOKABLE void setBrightness(QString brightness);
    Q_INVOKABLE void setState(QString state);

private slots:
    void onReplyFinished(QNetworkReply* reply);

signals:
    void infoReceived(QJsonObject obj);
    void modesReceived(QVariantList modes);
    void modeSelected(bool success);

private:
    QNetworkAccessManager* network_manager;
    QString base_url;

    void handleGetModesReply(QNetworkReply* reply);
    void handleSelectModeReply(QNetworkReply* reply);
    void handleGetInfoReply(QNetworkReply* reply);
    void handleSetBrightnessReply(QNetworkReply* reply);
    void handleSetStateReply(QNetworkReply* reply);
};

#endif // REQUESTHANDLER_H
