#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request(QUrl("http://127.0.0.1:8080/getModes"));

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]()
    {
        if(reply->error())
        {
            qDebug() << "Error: " << reply->errorString();
            reply->deleteLater();
            return;
        }

        QByteArray response_data = reply->readAll();
        QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
        QJsonArray json_array = json_doc.array();

        for(int i = 0; i < json_array.size(); ++i)
        {
            QJsonObject json_obj = json_array[i].toObject();
            QString item_text = json_obj["name"].toString();
            ui->modes->addItem(item_text, QVariant::fromValue(json_obj));
        }
        reply->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_color_clicked()
{
    QColorDialog color;
    color.exec();
}


void MainWindow::on_modes_currentIndexChanged(int index)
{
    QVariant currentData = ui->modes->itemData(index);
    QJsonObject json_obj = currentData.toJsonObject();
    int id = json_obj["id"].toInt();

    //QString url = "http://127.0.0.1:8080/selectMode?mode_id=" + json_obj["id"].toString();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request(QUrl("http://127.0.0.1:8080/selectMode?mode_id=" + QString::number(id)));
    qDebug() << currentData;
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, [=]()
    {
        if(reply->error())
        {
            qDebug() << "Error: " << reply->errorString();
            reply->deleteLater();
            return;
        }
        reply->deleteLater();
    });
}

