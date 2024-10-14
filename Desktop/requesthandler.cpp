#include "requesthandler.h"

RequestHandler::RequestHandler(QObject *parent)
    : QObject(parent)
{
}
void RequestHandler::getModes()
{
    QNetworkRequest request(QUrl("http://127.0.0.1:8080/getModes"));
    QNetworkReply *reply = manager->get(request);
}
void RequestHandler::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (jsonDoc.isObject())
        {
            QJsonObject jsonObj = jsonDoc.object();
            QJsonArray modesArray = jsonObj["modes"].toArray();
            QVariantList modesList;
            for (const QJsonValue &value : modesArray)
            {
                modesList.append(value.toString());
            }
            emit modesReceived(modesList);
        }
    }
    else
    {
        qDebug() << "Error:" << reply->errorString();
    }
    reply->deleteLater();
}
