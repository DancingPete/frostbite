#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QProgressBar>
#include <QTimer>
#include <QReadWriteLock>

class MainWindow;

class TimerBar : public QObject {
    Q_OBJECT

public:
    explicit TimerBar(QObject *parent = 0);
    ~TimerBar();

    void load();
    void add();
    bool isActive();

private:
    MainWindow* mainWindow;
    QProgressBar* timerProgress;
    QTimer* timer;
    QReadWriteLock lock;

    int maxValue;

signals:
    
public slots:
    void setTimer(int);

private slots:
    void intervalEvent();
    
};

#endif // TIMER_H
