////////////////////////////////////////
//  File      : dateclock.h           //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

// date and clock on systray

////////////////////////////////////////

#ifndef DATECLOCK_H
#define DATECLOCK_H

//#include "../src/defs.h"
#include <QLabel>
#include <QDate>
#include <QSettings>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
#include <QFont>
#include <QFontMetrics>
#include <QString>
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>

#include "../inc/popup.h"

////////////////////////////////////////

class Dateclock : public QLabel
{
    Q_OBJECT

public:
    Dateclock(QWidget *parent=0);
    ~Dateclock();
    void update_style();
    void read_settings();

public slots:
    void timeout(void);

protected:
    void mousePressEvent(QMouseEvent *);

protected:
    void paintEvent(QPaintEvent *);

private:
    QTime time;
    QDate date;
    QColor date_col;
    QColor clock_col;
    QTimer *timer;
    PopupWindow *popup;
};

#endif
