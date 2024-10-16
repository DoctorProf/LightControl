#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include "requesthandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    RequestHandler request_handler;
    engine.rootContext()->setContextProperty("request_handler", &request_handler);
    engine.load(QUrl(QStringLiteral("qrc:/Desktop/main.qml")));

    request_handler.getModes();
    request_handler.getInfo();
    return app.exec();
}
