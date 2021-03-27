#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) : QPlainTextEdit(parent) {
    mainWindow = (MainWindow*)parent;       
    windowFacade = mainWindow->getWindowFacade();
    settings = GeneralSettings::getInstance();
    dictionarySettings = DictionarySettings::getInstance();
    snapshot = new Snapshot(this);

    this->setObjectName(WINDOW_TITLE_MAIN);

    this->loadSettings();   
    this->buildContextMenu();

    this->setFocusPolicy(Qt::NoFocus);
    this->setReadOnly(true);
    this->setUndoRedoEnabled(false);
    this->document()->setMaximumBlockCount(GAME_WINDOW_LIMIT);

    _append = true;
    _stream = false;

    connect(this, SIGNAL(copyAvailable(bool)), this, SLOT(enableCopy(bool)));

    /* workaround for bottom margin */
    setViewportMargins(0, 0, 0, -6);    
}

void GameWindow::setAppend(bool append) {
    this->_append = append;
}

bool GameWindow::append() {
    return this->_append;
}

void GameWindow::setStream(bool stream) {
    this->_stream = stream;
}

bool GameWindow::stream() {
    return this->_stream;
}

void GameWindow::showEvent(QShowEvent* event) {
    QPlainTextEdit::showEvent(event);
}

void GameWindow::loadSettings() {
    QFont font = settings->gameWindowFont();
    font.setStyleStrategy(QFont::PreferAntialias);
    this->setFont(font);

    QPalette p = this->viewport()->palette();
    p.setColor(QPalette::Text, settings->gameWindowFontColor());
    p.setColor(QPalette::Base, settings->gameWindowBackground());
    this->setPalette(p);
}

QColor GameWindow::getBgColor() {
    return viewport()->palette().color(QPalette::Base);
}

QColor GameWindow::getTextColor() {
    return viewport()->palette().color(QPalette::Text);
}

QTextDocument* GameWindow::getDocument() {
    return this->document();
}

QString GameWindow::getObjectName() {
    return this->objectName();
}

QPlainTextEdit* GameWindow::getMainWindow() {
    return this;
}

void GameWindow::buildContextMenu() {
    menu = new ContextMenu(this);
    appearanceAct = new QAction(tr("&Appearance\t"), this);
    menu->addAction(appearanceAct);
    connect(appearanceAct, SIGNAL(triggered()), this, SLOT(changeAppearance()));

    menu->addSeparator();

    
    lookupDictAct = new QAction(tr("&Lookup in Dictionary\t"), this);
    menu->addAction(lookupDictAct);
    lookupDictAct->setEnabled(false);
    connect(lookupDictAct, SIGNAL(triggered()), this, SLOT(lookupInDictionary()));
    
    copyAct = new QAction(tr("&Copy\t"), this);
    menu->addAction(copyAct);
    copyAct->setEnabled(false);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copySelected()));

    selectAct = new QAction(tr("&Select all\t"), this);
    menu->addAction(selectAct);
    connect(selectAct, SIGNAL(triggered()), this, SLOT(selectAll()));

    menu->addSeparator();

    saveAct = new QAction(tr("&Save as HTML\t"), this);
    menu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveAsHtml()));

    menu->addSeparator();

    clearAct = new QAction(tr("&Clear\t"), this);
    menu->addAction(clearAct);
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));
}

void GameWindow::changeAppearance() {
    mainWindow->openAppearanceDialog();
}

void GameWindow::saveAsHtml() {
    snapshot->save();
}

void GameWindow::contextMenuEvent(QContextMenuEvent *event) {
    QPoint point = event->globalPos();
    point.rx()--; point.ry()--;
    menu->exec(point);
}

void GameWindow::resizeEvent(QResizeEvent *event) {
    windowFacade->gameWindowResizeEvent(this);
    QPlainTextEdit::resizeEvent(event);
}

void GameWindow::mouseDoubleClickEvent(QMouseEvent *e) {
    QPlainTextEdit::mouseDoubleClickEvent(e);
    if (dictionarySettings->getDoubleClickEnabled() &&
        e->button() == Qt::LeftButton &&
        e->modifiers() == dictionarySettings->getDoubleClickModifier()) {
        lookupInDictionary();
    }
}

void GameWindow::enableCopy(bool enabled) {
    copyAct->setEnabled(enabled);
    lookupDictAct->setEnabled(enabled);
}


void GameWindow::lookupInDictionary() {
  QTextCursor textCursor = this->textCursor();
  if (textCursor.hasSelection()) {
    QString word = textCursor.selectedText().trimmed().toLower();
    if (word.size()) {
        mainWindow->getDictionaryService()->translate(word);
    }
  }
}

void GameWindow::copySelected() {
    this->copy();

    QTextCursor textCursor = this->textCursor();
    textCursor.clearSelection();
    this->setTextCursor(textCursor);
}

GameWindow::~GameWindow() {        
    delete appearanceAct;
    delete lookupDictAct;
    delete copyAct;
    delete selectAct;
    delete clearAct;
    delete saveAct;
    delete menu;
    delete snapshot;
}
