#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QtQuickControls2/QQuickStyle>
#include "Headers/requesthandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    RequestHandler request_handler;
    app.setWindowIcon(QIcon(":/icon/Resources/logo.ico"));
    engine.rootContext()->setContextProperty("request_handler", &request_handler);
    engine.load(QUrl(QStringLiteral("qrc:/Layouts/main.qml")));

    return app.exec();
}
