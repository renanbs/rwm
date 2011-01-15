////////////////////////////////////////
//  File      : launcher.h            //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

// the "Start" menu in the bottom-left of the dockbar
// manage the menu entry

////////////////////////////////////////

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "defs.h"
#include "rwm.h"
#include "manager.h"
#include "settings.h"
#include "runner.h"
#include "utils.h"

class Rwm;

////////////////////////////////////////

class Launcher : public QLabel
{
    Q_OBJECT

public:
    Launcher(Rwm *, QWidget *parent=0);
    ~Launcher();
    void read_settings();
    void init();
    void update_style();

public slots:
    void run_command(QAction *);
    
signals:
 
protected:
    void mousePressEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
	void paintEvent(QPaintEvent *);

private:
    QString launcher_pix;
    QString quit_pix;
    QString shutdown_pix;
    QString restart_pix;
    QString show_pix;
    QString settings_pix;
    QString refresh_pix;
    QString run_pix;
    QString manager_pix;
    int dock_position;
    int dock_height;
    Rwm *app;
    QAction *quit;
    QAction *shutdown;
    QAction *restart;
    QAction *refresh;
    QAction *run;
    QAction *show_desk;
    QAction *settings;
    QAction *manager;
    QSettings *rwm;
    QMenu *main_menu;
	bool zoom;
};

#endif
