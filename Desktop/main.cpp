#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "requesthandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Desktop/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    RequestHandler request_handler;

    QObject::connect(&request_handler, &RequestHandler::modesReceived, [&engine](QVariantList &modes)
    {
           QObject *rootObject = engine.rootObjects().first();
           if (rootObject)
           {
               QObject *modeComboBox = rootObject->findChild<QObject*>("modeComboBox");
               if (modeComboBox)
               {
                   QMetaObject::invokeMethod(modeComboBox, "setModes", Q_ARG(QVariant, modes));
               }
           }
       });
       engine.rootContext()->setContextProperty("request_handler", &request_handler);

       request_handler.getModes();

    return app.exec();
}
