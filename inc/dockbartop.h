#ifndef DOCKBARTOP_H
#define DOCKBARTOP_H

#include <QLabel>
#include "../inc/launcher.h"
#include "../inc/systray.h"
#include "../inc/dockapp.h"
#include "../inc/dateclock.h"
#include "filedialog.h"

class Frame;
class Dockapp;
class Systray;
class Rwm;
class Launcher;
class Filedialog;


class DockBarTop : public QLabel
{
	Q_OBJECT      
	
	public:
		DockBarTop (Rwm *, QWidget *parent=0);
		~DockBarTop ();
		void readSettings ();
		void setGeometryDockTop ();
		void update_style();
		void createDockApp(const QString &, const QString &, QWidget *parent);
		void restoreDockApps();
		
		Systray *system_tray() const
		{
			return sys;
		}

	public slots:
		void removeDockApp (Dockapp *);
		void runRightClickMenu (QAction *);

	protected:
		void mousePressEvent(QMouseEvent *);
		void dragEnterEvent(QDragEnterEvent *);
		void dragMoveEvent(QDragMoveEvent *);

	private:
		QList<Dockapp *> dockApps;
		int dockHeight;
		int dockWidth;
		int dockPosition;
		QString dockPix;
		QString appShorcutPix;
		QSettings *rwm;
		QMenu *rightClickMenu;
		QHBoxLayout *dockLayout;
		QHBoxLayout *appLayout;
		QWidget *appWidget;
		Launcher *lchr;
		Systray *sys;
		Dateclock *clk;
		Rwm *app;
		Filedialog *fileDialog;
};

#endif // DOCKBARTOP_H
