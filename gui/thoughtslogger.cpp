#include "thoughtslogger.h"
#include "textutils.h"

ThoughtsLogger::ThoughtsLogger(QObject*) {
    rxRemoveTags.setPattern("<[^>]*>");
}

void ThoughtsLogger::addText(QString text) {
    mMutex.lock();
    dataQueue.enqueue(text);
    mMutex.unlock();
}

void ThoughtsLogger::run() {
    while(!dataQueue.isEmpty()) {
        mMutex.lock();
        localData = dataQueue.dequeue();
        mMutex.unlock();
        log(localData);
    }
}

void ThoughtsLogger::log(QString logText) {
    TextUtils::htmlToPlain(logText);
    logger()->info(logText.remove(rxRemoveTags));
}

ThoughtsLogger::~ThoughtsLogger() {
}
