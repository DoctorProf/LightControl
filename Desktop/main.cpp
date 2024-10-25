#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QtQuickControls2/QQuickStyle>
#include "Headers/requesthandler.h"
#include "Headers/syncworker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    RequestHandler request_handler;
    app.setWindowIcon(QIcon(":/icon/Resources/logo.ico"));
    engine.rootContext()->setContextProperty("request_handler", &request_handler);
    engine.load(QUrl(QStringLiteral("qrc:/Desktop/Layouts/main.qml")));

    request_handler.getModes();
    request_handler.getSettings();

    // SyncWorker *worker = new SyncWorker(&request_handler);
    // QThread *thread = new QThread;
    // worker->moveToThread(thread);

    // QObject::connect(thread, &QThread::started, worker, &SyncWorker::syncData);
    // QObject::connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    // QObject::connect(worker, &QObject::destroyed, thread, &QThread::quit);

    // thread->start();

    return app.exec();
}
