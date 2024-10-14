#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>

class RequestHandler : public QObject
{
    Q_OBJECT
public:
    explicit RequestHandler(QObject *parent = nullptr);

    void getModes();
private slots:
    void onReplyFinished(QNetworkReply* reply);

signals:
    void modesReceived(QVariantList &modes);

private:
    QNetworkAccessManager* manager;
};

#endif // REQUESTHANDLER_H
