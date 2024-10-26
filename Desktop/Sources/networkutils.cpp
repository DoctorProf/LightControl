#include "../Headers/networkutils.h"

QString network_utils::extractResponseMessage(QNetworkReply* reply)
{
    QJsonObject obj = extractJsonObj(reply);
    QString message = obj.value("status").toString() + " " + obj.value("description").toString();
    return message;
}
QJsonObject network_utils::extractJsonObj(QNetworkReply* reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject obj = json_doc.object();
    return obj;
}
QVariantList network_utils::extractVariants(QNetworkReply* reply)
{
    QByteArray response_data = reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QVariantList variant_list;
    for (const QJsonValue &value : json_array)
    {
        variant_list.append(value);
    }
    return variant_list;
}
