#ifndef DEATHSWINDOW_H
#define DEATHSWINDOW_H

#include <QObject>
#include <QDockWidget>

class MainWindow;
class WindowFacade;
class GenericWindow;
class DeathsLogger;
class ClientSettings;
class WindowWriterThread;

class DeathsWindow : public QObject {
    Q_OBJECT

public:
    DeathsWindow(QObject *parent = 0);
    ~DeathsWindow();

    QDockWidget* getDockWidget();

private:
    MainWindow* mainWindow;
    WindowFacade* windowFacade;
    GenericWindow* window;
    QDockWidget* dock;
    WindowWriterThread* writer;
    DeathsLogger* deathsLogger;
    ClientSettings* clientSettings;

    bool visible;

    void log(QString text);

public slots:
    void setVisible(bool);
    void write(QString text);

};

#endif // DEATHSWINDOW_H
