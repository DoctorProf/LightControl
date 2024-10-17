#include "syncworker.h"

SyncWorker::SyncWorker(RequestHandler *handler)
    : handler(handler)
{

}
void SyncWorker::syncData()
{
    while(true)
    {
        handler->getInfo();
        QThread::sleep(1);
    }
}
