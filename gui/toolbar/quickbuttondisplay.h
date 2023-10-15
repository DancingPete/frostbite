#ifndef QUICKBUTTONDISPLAY_H
#define QUICKBUTTONDISPLAY_H

#include <QObject>
#include <QtGui>
#include <QToolButton>
#include <QHBoxLayout>

#define T_QB_W 28
#define T_QB_H 28

class Toolbar;
class GeneralSettings;
class QuickButtonEditDialog;

class QuickButtonDisplay : public QObject {
    Q_OBJECT

public:
    explicit QuickButtonDisplay(QObject *parent = 0);
    ~QuickButtonDisplay();

    QWidget *create();

    void setScale(float scale);

    void reloadSettings();

private:
    QToolButton* actionButton(const char*, const char*, QString);
    Toolbar* toolBar;
    GeneralSettings* settings;
    QuickButtonEditDialog* editDialog;
    QWidget* buttonWidget;
    QHBoxLayout* hLayout;

    QToolButton* sword;
    QToolButton* bow;
    QToolButton* shield;
    QToolButton* bag;
    QToolButton* xsword;
    QToolButton* xbow;
    QToolButton* xshield;

private slots:
    void swordButtonEdit(const QPoint&);
    void bowButtonEdit(const QPoint&);
    void shieldButtonEdit(const QPoint&);
    void bagButtonEdit(const QPoint&);
    void xswordButtonEdit(const QPoint&);
    void xbowButtonEdit(const QPoint&);
    void xshieldButtonEdit(const QPoint&);

signals:

public slots:

};

#endif // QUICKBUTTONDISPLAY_H
