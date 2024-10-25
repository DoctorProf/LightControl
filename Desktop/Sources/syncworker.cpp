#include "Headers/syncworker.h"

SyncWorker::SyncWorker(RequestHandler *handler)
    : handler(handler)
{

}
void SyncWorker::syncData()
{
    while(true)
    {
        QThread::sleep(1);
    }
}
