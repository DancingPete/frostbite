#include "volumecontroldialog.h"
#include "ui_volumecontroldialog.h"

#include "mainwindow.h"
#include "clientsettings.h"


VolumeControlDialog::VolumeControlDialog(QWidget *parent) : QDialog(parent), ui(new Ui::VolumeControlDialog) {
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setFixedSize(100, 210);

    mainWindow = (MainWindow*)qobject_cast<QObject *>(parent);
    clientSettings = ClientSettings::getInstance();

    int volume = clientSettings->getParameter("Audio/volume", 80).toInt();
    this->setVolumeText(volume);
    ui->volumeSlider->setValue(volume);

    bool muted = clientSettings->getParameter("Audio/muted", false).toBool();
    this->muteSounds(muted);

    connect(ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeValueChanged(int)));
    connect(ui->volumeSlider, SIGNAL(sliderReleased()), this, SLOT(volumeSelected()));
    connect(ui->volumeMuted, SIGNAL(stateChanged(int)), this, SLOT(mutedValueChanged(int)));

    connect(this, SIGNAL(volumeChanged(int)), mainWindow, SLOT(menuVolumeChanged(int)));
    connect(this, SIGNAL(volumeMuted(bool)), mainWindow, SLOT(menuVolumeMuted(bool)));
    connect(mainWindow, SIGNAL(volumeMuted(bool)), this, SLOT(muteSounds(bool)));
}

void VolumeControlDialog::volumeValueChanged(int value) {
    this->setVolumeText(value);
}

void VolumeControlDialog::volumeSelected() {
    int volume = ui->volumeSlider->value();
    clientSettings->setParameter("Audio/volume", ui->volumeSlider->value());
    emit volumeChanged(volume);
}

void VolumeControlDialog::mutedValueChanged(int state) {
    bool checked = state == Qt::CheckState::Checked;
    clientSettings->setParameter("Audio/muted", checked);
    emit volumeMuted(checked);
}

void VolumeControlDialog::setVolumeText(int value) {
    ui->volumeValueLabel->setText(QString::number(value) + "%");
}

void VolumeControlDialog::muteSounds(bool checked) {
    ui->volumeMuted->setChecked(checked);
    ui->volumeMuted->setToolTip(checked ? "Unmute sounds" : "Mute sounds");
}

VolumeControlDialog::~VolumeControlDialog() {
    delete ui;
}
