#include "menuhandler.h"

#include "mainwindow.h"
#include "windowfacade.h"
#include "connectwizard.h"
#include "text/highlight/highlightdialog.h"
#include "macrodialog.h"
#include "text/alter/alterdialog.h"
#include "appearancedialog.h"
#include "aboutdialog.h"
#include "scripteditdialog.h"
#include "profileadddialog.h"
#include "clientsettings.h"
#include "scriptsettingsdialog.h"
#include "audio/volumecontroldialog.h"
#include "dict/dictionarydialog.h"
#include "compass/compassview.h"
#include "toolbar/toolbar.h"
#include "tcpclient.h"

MenuHandler::MenuHandler(QObject *parent) : QObject(parent) {
    mainWindow = (MainWindow*)parent;
    clientSettings = ClientSettings::getInstance();

    connectWizard = new ConnectWizard(qobject_cast<QWidget *>(parent));
    highlightDialog = new HighlightDialog(qobject_cast<QWidget *>(parent));
    macroDialog = new MacroDialog(qobject_cast<QWidget *>(parent));
    alterDialog = new AlterDialog(qobject_cast<QWidget *>(parent));
    appearanceDialog = new AppearanceDialog(qobject_cast<QWidget *>(parent));
    scriptSettingsDialog = new ScriptSettingsDialog(qobject_cast<QWidget *>(parent));
    aboutDialog = new AboutDialog(qobject_cast<QWidget *>(parent));
    scriptEditDialog = new ScriptEditDialog(qobject_cast<QWidget *>(parent));    
    volumeControlDialog = new VolumeControlDialog(qobject_cast<QWidget *>(parent));
    dictionaryDialog = new DictionaryDialog(qobject_cast<QWidget *>(parent));
    
    profileAddDialog = new ProfileAddDialog();

    windowFacade = mainWindow->getWindowFacade();

    connect(profileAddDialog, SIGNAL(updateMenu()), this, SLOT(loadProfilesMenu()));

    connect(scriptSettingsDialog, SIGNAL(settingsChanged()), mainWindow, SLOT(updateScriptSettings()));

    connect(mainWindow, SIGNAL(profileChanged()), this, SLOT(reloadSettings()));
    connect(mainWindow, SIGNAL(profileChanged()), macroDialog, SLOT(reloadSettings()));
    connect(mainWindow, SIGNAL(profileChanged()), appearanceDialog, SLOT(reloadSettings()));

    connect(this, SIGNAL(compassLocked(bool)), windowFacade->getCompassView(), SLOT(setCompassLocked(bool)));
    connect(this, SIGNAL(compassVisible(bool)), windowFacade->getCompassView(), SLOT(setCompassVisible(bool)));
    connect(this, SIGNAL(compassAnchored(bool)), windowFacade->getCompassView(), SLOT(setCompassAnchored(bool)));
    connect(this, SIGNAL(resetCompass()), windowFacade->getCompassView(), SLOT(resetCompass()));

    this->loadLoggingMenu();
    this->loadToolbarMenu();
    this->loadWindowMenu();
    this->loadCompassMenu();

    menuReady = true;
}

void MenuHandler::openConnectDialog() {
    connectWizard->show();
}

void MenuHandler::openAppearanceDialog() {
    appearanceDialog->show();
}

void MenuHandler::reloadSettings() {
    alterDialog->updateSettings();

    highlightDialog->updateSettings();
    highlightDialog->loadSettings();

    this->loadProfilesMenu();
}

void MenuHandler::menuTriggered(QAction* action) {
    if(action->objectName() == "actionConnect") {
        connectWizard->show();
    } else if (action->objectName() == "actionDisconnect") {
        mainWindow->getTcpClient()->disconnectFromServer();
    } else if(action->objectName() == "actionText_Highlight") {
        highlightDialog->show();
    } else if (action->objectName() == "actionMacros") {
        macroDialog->show();
    } else if (action->objectName() == "actionSubstitute") {
        alterDialog->show();
    } else if (action->objectName() == "actionAppearance") {
        appearanceDialog->show();
    } else if(action->objectName() == "actionDictionary") {
        dictionaryDialog->show();
    } else if(action->objectName() == "actionExit") {
        mainWindow->close();
    } else if(action->objectName() == "actionAbout") {
        aboutDialog->show();
    } else if(action->objectName() == "actionScriptEdit") {
        scriptEditDialog->show();        
    } else if(action->objectName() == "actionScriptSettings") {
        scriptSettingsDialog->show();
    } else if(action->objectName() == "actionCreate_new_profile") {
        profileAddDialog->show();
    } else if(action->objectName() == "actionReference_Manual") {
        QDesktopServices::openUrl(QUrl(USER_GUIDE_URL));
    } else if(action->objectName() == "actionLogMain") {
        clientSettings->setParameter("Logging/main", action->isChecked());
    } else if(action->objectName() == "actionLogThoughts") {
        clientSettings->setParameter("Logging/thoughts", action->isChecked());
    } else if(action->objectName() == "actionLogConversations") {
        clientSettings->setParameter("Logging/conversations", action->isChecked());
    } else if(action->objectName() == "actionLogArrivals") {
        clientSettings->setParameter("Logging/arrivals", action->isChecked());
    } else if(action->objectName() == "actionLogDeaths") {
        clientSettings->setParameter("Logging/deaths", action->isChecked());
    } else if(action->objectName() == "actionLogDebug") {
        clientSettings->setParameter("Logging/debug", action->isChecked());
    } else if(action->objectName() == "actionLogAuth") {
        clientSettings->setParameter("Logging/auth", action->isChecked());
    } else if(action->objectName() == "actionWindowSave") {
        mainWindow->saveWindow();        
    } else if(action->objectName() == "actionLockWindows") {
        this->lockWindows(action);
    } else if(action->objectName() == "actionToolWieldLeft") {
        clientSettings->setParameter("Toolbar/wieldLeft", action->isChecked());
        mainWindow->getToolbar()->setWieldLeftVisible(action->isChecked());
    } else if(action->objectName() == "actionToolWieldRight") {
        clientSettings->setParameter("Toolbar/wieldRight", action->isChecked());
        mainWindow->getToolbar()->setWieldRightVisible(action->isChecked());
    } else if(action->objectName() == "actionToolSpell") {
        clientSettings->setParameter("Toolbar/spell", action->isChecked());
        mainWindow->getToolbar()->setSpellVisible(action->isChecked());
    } else if(action->objectName() == "actionToolActiveSpells") {
        clientSettings->setParameter("Toolbar/activeSpells", action->isChecked());
        mainWindow->getToolbar()->setActiveSpellsVisible(action->isChecked());
    } else if(action->objectName() == "actionToolStatus") {
        clientSettings->setParameter("Toolbar/status", action->isChecked());
        mainWindow->getToolbar()->setStatusVisible(action->isChecked());
    } else if(action->objectName() == "actionToolButtons") {
        clientSettings->setParameter("Toolbar/buttons", action->isChecked());
        mainWindow->getToolbar()->setButtonsVisible(action->isChecked());
    } else if(action->objectName() == "actionToolVitals") {
        clientSettings->setParameter("Toolbar/vitals", action->isChecked());
        mainWindow->getToolbar()->setVitalsVisible(action->isChecked());
    } else if(action->objectName() == "actionToolMute") {
        clientSettings->setParameter("Toolbar/muted", action->isChecked());
        mainWindow->getToolbar()->setMuteVisible(action->isChecked());
    } else if(action->objectName() == "actionToolFullScreen") {
        clientSettings->setParameter("Toolbar/fullScreen", action->isChecked());
        mainWindow->getToolbar()->setFullScreenVisible(action->isChecked());
    } else if(action->objectName() == "actionToolLarge") {
        clientSettings->setParameter("Toolbar/size", "large");
        mainWindow->setToolSize("large");
        mainWindow->setToolbarScale(1.1);
    } else if(action->objectName() == "actionToolNormal") {
        clientSettings->setParameter("Toolbar/size", "normal");
        mainWindow->setToolSize("normal");
        mainWindow->setToolbarScale(1);
    } else if(action->objectName() == "actionToolSmall") {
        clientSettings->setParameter("Toolbar/size", "small");
        mainWindow->setToolSize("small");
        mainWindow->setToolbarScale(0.9);
    } else if(action->objectName() == "actionToolXsmall") {
        clientSettings->setParameter("Toolbar/size", "x-small");
        mainWindow->setToolSize("x-small");
        mainWindow->setToolbarScale(0.8);
    } else if(action->objectName() == "actionMapReload") {
        mainWindow->reloadMaps();
    } else if(action->objectName() == "actionMapShow") {
        mainWindow->showMaps();
    } else if(action->objectName() == "actionCompassVisible") {
        clientSettings->setParameter("Compass/visible", action->isChecked());
        emit compassVisible(action->isChecked());
    } else if(action->objectName() == "actionLockCompass") {
        clientSettings->setParameter("Compass/locked", action->isChecked());
        emit compassLocked(action->isChecked());
    } else if(action->objectName() == "actionCompassBottomRight") {
        clientSettings->setParameter("Compass/anchor", action->isChecked() ? "bottomRight" : "");
        emit compassAnchored(action->isChecked());
    } else if(action->objectName() == "actionCompassResetPosition") {
        emit resetCompass();
    } else if(action->objectName() == "actionVolume") {
        volumeControlDialog->show();
    }
}

void MenuHandler::menuHovered(QAction* action) {
    if(action->objectName() == "actionLoad_profile") {
        if(menuReady) {
            QTimer::singleShot(5000, this, SLOT(setMenuReady()));
            this->loadProfilesMenu();
            menuReady = false;
        }
    }
}

void MenuHandler::setMenuReady() {
    menuReady = true;
}

void MenuHandler::profileTriggered(QAction* action) {
    if(action->isChecked()) {
        QPair<QString, QString> profile = action->data().value<QPair<QString, QString>>();
        mainWindow->updateProfileSettings(profile.second, profile.first);
    } else {
        mainWindow->updateProfileSettings("", "");
    }    
    this->loadProfilesMenu();
}

void MenuHandler::lockWindows(QAction* action) {
    if(action->isChecked()) {
        mainWindow->getWindowFacade()->lockWindows();
    } else {
        mainWindow->getWindowFacade()->unlockWindows();
    }
    clientSettings->setParameter("Window/lock", action->isChecked());
}

void MenuHandler::loadProfilesMenu() {
    QList<QPair<QString, QStringList>> profiles;

    QDir dir(QApplication::applicationDirPath() + "/profiles");
    profiles << qMakePair(QString("L"), dir.entryList(QDir::NoDotAndDotDot | QDir::Dirs, QDir::Name));

    QDir homeDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/profiles");
    profiles << qMakePair(QString("H"), homeDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs, QDir::Name));

    profilesMenu = new QMenu(mainWindow);

    QString currentName = clientSettings->getParameter("Profile/name", "").toString();
    QString currentType = clientSettings->getParameter("Profile/type", "").toString();

    QPair<QString, QStringList> profile;
    foreach(profile, profiles) {
        QString type = profile.first;

        foreach(QString name, profile.second) {
            action = new QAction(name + " (" + type + ")", profilesMenu);
            action->setCheckable(true);
            action->setData(QVariant::fromValue(qMakePair(type, name)));

            if(currentName == name && currentType == type) {
                action->setChecked(true);
            }
            profilesMenu->addAction(action);
        }
    }

    mainWindow->insertProfilesMenu(profilesMenu);

    connect(profilesMenu, SIGNAL(triggered(QAction*)), this, SLOT(profileTriggered(QAction*)));
}

void MenuHandler::loadLoggingMenu() {
    mainWindow->setLogMain(clientSettings->getParameter("Logging/main", false).toBool());
    mainWindow->setLogThoughts(clientSettings->getParameter("Logging/thoughts", false).toBool());
    mainWindow->setLogConversations(clientSettings->getParameter("Logging/conversations", false).toBool());
    mainWindow->setLogArrivals(clientSettings->getParameter("Logging/arrivals", false).toBool());
    mainWindow->setLogDeaths(clientSettings->getParameter("Logging/deaths", false).toBool());
    mainWindow->setLogDebug(clientSettings->getParameter("Logging/debug", false).toBool());
    mainWindow->setLogAuth(clientSettings->getParameter("Logging/auth", false).toBool());
}

void MenuHandler::loadToolbarMenu() {
    mainWindow->setMenuWieldLeftVisible(clientSettings->getParameter("Toolbar/wieldLeft", true).toBool());
    mainWindow->setMenuWieldRightVisible(clientSettings->getParameter("Toolbar/wieldRight", true).toBool());
    mainWindow->setMenuSpellVisible(clientSettings->getParameter("Toolbar/spell", true).toBool());
    mainWindow->setMenuActiveSpellsVisible(clientSettings->getParameter("Toolbar/activeSpells", true).toBool());
    mainWindow->setMenuStatusVisible(clientSettings->getParameter("Toolbar/status", true).toBool());
    mainWindow->setMenuButtonsVisible(clientSettings->getParameter("Toolbar/buttons", true).toBool());
    mainWindow->setMenuVitalsVisible(clientSettings->getParameter("Toolbar/vitals", true).toBool());
    mainWindow->setMenuMutedVisible(clientSettings->getParameter("Toolbar/muted", false).toBool());
    mainWindow->setFullScreenVisible(clientSettings->getParameter("Toolbar/fullScreen", false).toBool());
    mainWindow->setToolSize(clientSettings->getParameter("Toolbar/size", "normal").toString());
}

void MenuHandler::loadWindowMenu() {
   mainWindow->setWindowLocked(clientSettings->getParameter("Window/lock", false).toBool());
}

void MenuHandler::loadCompassMenu() {
    mainWindow->setCompassLocked(clientSettings->getParameter("Compass/locked", true).toBool());
    mainWindow->setCompassAnchored(clientSettings->getParameter("Compass/anchor", "bottomRight").toString() != "");
    mainWindow->setCompassVisible(clientSettings->getParameter("Compass/visible", true).toBool());
}

MenuHandler::~MenuHandler() {
    delete appearanceDialog;
    delete highlightDialog;
    delete macroDialog;
    delete alterDialog;
    delete aboutDialog;
    delete scriptEditDialog;
    delete profileAddDialog;
    delete profilesMenu;
}

