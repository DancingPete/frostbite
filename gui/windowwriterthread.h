#ifndef WINDOWWRITERTHREAD_H
#define WINDOWWRITERTHREAD_H

#include <QObject>
#include <QThread>
#include <QPlainTextEdit>
#include <QQueue>
#include <QMutex>
#include "concurrentqueue.h"

class Highlighter;
class Alter;
class WindowInterface;
class MainWindow;
class WindowInterface;

class WindowWriterThread : public QThread {
    Q_OBJECT

public:
    WindowWriterThread(QObject *parent, WindowInterface* window);
    ~WindowWriterThread();

    virtual void run();

private:
    ConcurrentQueue<QString> dataQueue;
    QPlainTextEdit* textEdit;

    Highlighter* highlighter;
    Alter* alter;

    MainWindow* mainWindow;
    QRegExp rxRemoveTags;
    WindowInterface *window;

    void write(QString);
    QString process(QString text, QString win);

    void setText(QString);

    bool exit;

public slots:
    void addText(QString);
    void updateSettings();

signals:
    void writeStream(const QString&);
    void writeText(const QString&);
    void clearText();

};

#endif // WINDOWWRITERTHREAD_H
