#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include "Headers/requesthandler.h"

class SyncWorker : public QObject
{
    Q_OBJECT
public:
    SyncWorker(RequestHandler *handler = nullptr);

public slots:
    void syncData();

private:
    RequestHandler *handler;
};
