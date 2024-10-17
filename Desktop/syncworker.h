#ifndef SYNCWORKER_H
#define SYNCWORKER_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include "requesthandler.h"

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

#endif // SYNCWORKER_H
