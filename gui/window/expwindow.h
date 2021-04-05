#ifndef EXPWINDOW_H
#define EXPWINDOW_H

#include <QObject>
#include <QDockWidget>
#include <QMap>

class MainWindow;
class WindowFacade;
class GridWindow;
class GridWriterThread;
class GameDataContainer;

typedef QMap<QString, QString> GridItems;

class GridWriterThread;

class ExpWindow : public QObject {
    Q_OBJECT

public:
    ExpWindow(QObject *parent = 0);
    ~ExpWindow();

    QDockWidget* getDockWidget();

private:
    MainWindow* mainWindow;
    WindowFacade* windowFacade;
    GridWindow* window;
    GridWriterThread* writer;
    GameDataContainer* gameDataContainer;

    QDockWidget* dock;

public slots:
    void write(QString name, QString text);
    void writeExpWindow(GridItems items);
};

#endif // EXPWINDOW_H
