#ifndef SCRIPT_H
#define SCRIPT_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QMutex>
#include <QReadWriteLock>

class ScriptService;
class ClientSettings;

class Script : public QObject {
    Q_OBJECT

public:
    Script(QObject *parent = 0);
    ~Script();

    void execute(QString, QList<QString>);

    bool isRunning();  
    QString currentFileName();

private:
    ScriptService* scriptService;
    QProcess* script_proc;

    ClientSettings* clientSettings;

    QString path;
    QString rubyPath;
    QString scriptPath;
    QString ext;
    QString fileName;    

    bool running;

    QMutex procMutex;
    QReadWriteLock lock;

signals:

public slots:
    void killScript();
    void sendMessage(QByteArray);

private slots:
    void displayOutputMsg();
    void displayErrorMsg();
    void start();
    void finish(int);
    void handleError(QProcess::ProcessError);
};

#endif // SCRIPT_H
