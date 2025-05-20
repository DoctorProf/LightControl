#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QtQuickControls2/QQuickStyle>
#include "Headers/requesthandler.h"
#include "Headers/colordialoghelper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    RequestHandler request_handler;
    ColorDialogHelper color_dialog_helper;

    app.setWindowIcon(QIcon(":/icon/Resources/logo.ico"));

    engine.rootContext()->setContextProperty("request_handler", &request_handler);
    engine.rootContext()->setContextProperty("color_dialog_helper", &color_dialog_helper);

    engine.load(QUrl(QStringLiteral("qrc:/Layouts/main.qml")));

    return app.exec();
}

