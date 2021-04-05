#ifndef VOLUMECONTROLDIALOG_H
#define VOLUMECONTROLDIALOG_H

#include <QDialog>

namespace Ui {
class VolumeControlDialog;
}

class ClientSettings;
class MainWindow;

class VolumeControlDialog : public QDialog {
    Q_OBJECT

public:
    explicit VolumeControlDialog(QWidget *parent = 0);
    ~VolumeControlDialog();

private:
    Ui::VolumeControlDialog *ui;

    ClientSettings* clientSettings;
    MainWindow* mainWindow;

    void setVolumeText(int value);    

public slots:
    void volumeValueChanged(int);
    void mutedValueChanged(int);
    void volumeSelected();
    void muteSounds(bool checked);

signals:
    void volumeChanged(int);
    void volumeMuted(bool);

};

#endif // VOLUMECONTROLDIALOG_H
