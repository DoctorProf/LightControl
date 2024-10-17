#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include "requesthandler.h"
#include "syncworker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    RequestHandler request_handler;
    engine.rootContext()->setContextProperty("request_handler", &request_handler);
    engine.load(QUrl(QStringLiteral("qrc:/Desktop/main.qml")));

    request_handler.getModes();
    request_handler.getInfo();

    // SyncWorker *worker = new SyncWorker(&request_handler);
    // QThread *thread = new QThread;
    // worker->moveToThread(thread);

    // QObject::connect(thread, &QThread::started, worker, &SyncWorker::syncData);
    // QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    // QObject::connect(worker, &QObject::destroyed, thread, &QThread::quit);

    // thread->start();

    return app.exec();
}
