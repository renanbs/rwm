#ifndef DOCKBARTOP_H
#define DOCKBARTOP_H

#include <QLabel>
// #include <QSpacerItem>
#include "../inc/defs.h"
#include "../inc/launcher.h"
#include "../inc/systray.h"
#include "../inc/dockicon.h"
#include "../inc/dockapp.h"
//#include "dockmenu.h"
#include "../inc/dateclock.h"
//#include "filedialog.h"

//class Frame;
//class Dockapp;
class Dockicon;
class Systray;
class Rwm;
class Launcher;
//class Filedialog;


class DockBarTop : public QLabel
{
	Q_OBJECT      // uncomment later
   
	public:
		DockBarTop (Rwm *, QWidget *parent=0);
		~DockBarTop ();
		void add_dockicon(Frame *);
		void remove_dockicon(Frame *);
		void update_dockicon_size();
		void readSettings ();
		void setGeometryDockTop ();
		void update_style();
		void remove_dockicon(Window);
		void update_dockicon_name(const QString &, Frame *);
		
		Systray *system_tray() const
		{
			return sys;
		}
		
	public slots:
		void remove_dockicon(Dockicon *);
		
	private:
       QHash<int, Dockicon *> dock_icons; // mapping Frame and Dockicon (key=frame win_id value=Dockicon)
//        QList<Dockapp *> dock_apps;
//        QList<Dockmenu *> dock_menus;
		int d_length;   //dockicon lenght
		int dockHeight;
		int dockWidth;
		int dockPosition;
		QString dockPix;
//        QString arrow_pix;
		QString app_link_pix;
		QSettings *rwm;
//        QMenu *menu;
		QHBoxLayout *dockLayout;
		QHBoxLayout *icon_layout;
//        QHBoxLayout *app_layout;
//        QHBoxLayout *menu_layout;
//        QWidget *d_app_widget;
		QWidget *d_icon_widget;
//        QWidget *d_menu_widget;
		Launcher *lchr;
		Dockicon *d_icon;
		Systray *sys;
		Dateclock *clk;
		Rwm *app;
		Dockapp *shortCut;
//        Filedialog *file_dialog;
// 		QSpacerItem *spacer;
};

#endif // DOCKBARTOP_H
