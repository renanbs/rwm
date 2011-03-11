#include "../inc/dockbartop.h"
#include "../inc/paths.h"
#include "../inc/defs.h"

DockBarTop::DockBarTop (Rwm *a, QWidget *parent) : QLabel(parent)
{
	app = a;
	fileDialog = app->get_file_dialog();
	dockLayout = new QHBoxLayout (this);
	dockLayout->setContentsMargins (0, 0, 0, 0);
	dockLayout->setSpacing (1);
	dockLayout->setSizeConstraint (QLayout::SetNoConstraint);
	setAcceptDrops (true); // for drag and drop from Filedialog
	setAttribute (Qt::WA_AlwaysShowToolTips);
	readSettings ();

	rightClickMenu = new QMenu (this);
	rightClickMenu->addAction (QIcon (appShorcutPix), tr("Add App to Dock Bar..."));
	connect (rightClickMenu, SIGNAL (triggered(QAction *)), this, SLOT(runRightClickMenu(QAction*)));

	setGeometryDockTop();

    // add launcher to dockbar
//     lchr = new Launcher (a, this);
	lchr = new Launcher (a);
	lchr->setFixedSize (dockHeight - 1, dockHeight - 1);

    //Dock Apps
//    // for set dockapp on dockbar
	appWidget = new QWidget();
    // add systray to dockbar
	sys = new Systray(this);
//     add clock to dockbar
	clk = new Dateclock(this);
	clk->setFixedSize(dockHeight * 2, dockHeight - 1);

	appLayout = new QHBoxLayout();
	appWidget->setLayout(appLayout);
	appLayout->setAlignment(Qt::AlignLeft);
	appLayout->setContentsMargins(0, 0, 0, 0);
	appLayout->setSpacing(1);


	dockLayout->addWidget (lchr);
	dockLayout->addWidget (appWidget);
	dockLayout->addWidget (sys);
	dockLayout->addWidget (clk);

	restoreDockApps (); // at startup, restore dockapps on dockbar
	
	setLayout (dockLayout);
	
	show();

}

DockBarTop::~DockBarTop ()
{
	delete rwm;
	delete dockLayout;
	delete app;
	delete clk;
	delete fileDialog;
}

void DockBarTop::setGeometryDockTop()
{
	setPixmap (dockPix);
	setScaledContents (true);

//  set dock width = to the desktop width
    dockWidth = QApplication::desktop ()->width ();

    int spaceDock = (QApplication::desktop ()->width () - dockWidth) / 2; // space left on right/left side of Dockbar

    if (dockPosition == 0) // 0 = bottom / 1 = top
        setGeometry (spaceDock, QApplication::desktop ()->height () - dockHeight, dockWidth, dockHeight);
    else // top
        setGeometry (spaceDock, 0, dockWidth, dockHeight);
}

void DockBarTop::readSettings()
{
    // get style path
    rwm = new QSettings(Paths::getConfigPath () + "/rwm.cfg", QSettings::IniFormat, this);
    rwm->beginGroup ("Style");
    QString stl_name = rwm->value ("name").toString();
    QString stl_path = rwm->value ("path").toString();
    QString path_name = stl_path + stl_name;
    rwm->endGroup (); //Style
    // get style values
    QSettings *styleDockTop = new QSettings (stl_path + stl_name, QSettings::IniFormat, this);
    styleDockTop->beginGroup ("DockBarTop");
    dockPix = stl_path + styleDockTop->value ("dockPix").toString();
    dockHeight = styleDockTop->value ("dockHeight").toInt();
    dockWidth = styleDockTop->value ("dockWidth").toInt();
    dockPosition = styleDockTop->value ("dockPosition").toInt();
    styleDockTop->endGroup(); //DockBarTop
    styleDockTop->beginGroup ("Other");
	// Path to the picture used in the right click menu to add applications to the dock bar
    appShorcutPix = stl_path + styleDockTop->value ("app_link_pix").toString();
    styleDockTop->endGroup (); //Other
}

void DockBarTop::mousePressEvent (QMouseEvent *event)
{
    if (event->button () == Qt::RightButton)
    {
        rightClickMenu->exec (event->globalPos ());
    }
}

void DockBarTop::runRightClickMenu (QAction *act)
{
    if (act->text().compare (tr("Add App to Dock Bar...")) == 0)
    {
        fileDialog->set_type (tr("Add App to Dock Bar:"), "OK_Close");

        if (fileDialog->exec() == QDialog::Accepted)
        {
            QString path = fileDialog->get_selected_path();
            QString name = fileDialog->get_selected_name();
            QPoint pos = rightClickMenu->pos();
            QFileInfo pathinfo(path+name);

            if (! name.isEmpty() && pathinfo.isExecutable())
            {
                createDockApp (name, path, this);
            }
        }
    }
}

void DockBarTop::restoreDockApps()
{
    // read dockapp name, path and pixmap and restore on dockbar
    rwm->beginGroup("DockbarTop");
    rwm->beginGroup("App");

    for (int i = 0; i < rwm->childGroups().size(); i++)
    {
        rwm->beginGroup(rwm->childGroups().value(i)); // App name

        QString name = rwm->value("name").toString();
        QString exec = rwm->value("exec").toString();
        QString pix = rwm->value("pix").toString();
        Dockapp *d_app = new Dockapp(name, exec, pix, true, this);
        dockApps << d_app; // save the dockapp

        d_app->setFixedSize (dockHeight - 2, dockHeight - 2);
        appLayout->addWidget (d_app);

        connect(d_app, SIGNAL(destroy_dockapp(Dockapp *)), this, SLOT(removeDockApp(Dockapp *))); // delete dockapp form list

        rwm->endGroup(); // App name
    }
    rwm->endGroup(); //App
    rwm->endGroup(); //Dockapp
}

void DockBarTop::createDockApp(const QString &name, const QString &exec, QWidget *parent)
{
    Appicon appIcon; // get application icon
    QString pix = appIcon.get_app_icon(name);
    Dockapp *dApp = new Dockapp(name, exec, pix, true, parent); // new dockbar application
    dockApps << dApp; // save the new dockapp
    // save new dockapp name, path and pix
    rwm->beginGroup("DockbarTop");
    rwm->beginGroup("App");
    rwm->beginGroup(name);
    rwm->setValue("name", name);
    rwm->setValue("exec", exec);
    rwm->setValue("pix", pix);
    rwm->endGroup(); //name
    rwm->endGroup(); //App
    rwm->endGroup(); //Dockbar

    dApp->setFixedSize(dockHeight - 2, dockHeight - 2);
    appLayout->addWidget(dApp);

    connect(dApp, SIGNAL(destroy_dockapp(Dockapp *)), this, SLOT(removeDockApp(Dockapp *))); // delete dockapp form list
}

void DockBarTop::removeDockApp (Dockapp *dApp) // remove from "Delete link" right button mouse on Dockbar
{
    dockApps.removeOne(dApp);
    qDebug() << "Dockapp remove. Num. after deletion:" << dockApps.size();

	QString name = dApp->getAppName();
    rwm->beginGroup("DockbarTop");
    rwm->beginGroup("App");
    rwm->remove(name);
    rwm->endGroup(); // App
    rwm->endGroup(); // Dockbar
	
	dApp->close();
}
