#pragma once
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>

namespace network_utils
{
    QString extractResponseMessage(QNetworkReply* reply);
    QJsonObject extractJsonObj(QNetworkReply* reply);
    QVariantList extractVariants(QNetworkReply* reply);
}
