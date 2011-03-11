#include "../inc/dockbartop.h"
#include "../inc/paths.h"
#include "../inc/defs.h"

DockBarTop::DockBarTop (Rwm *a, QWidget *parent) : QLabel(parent)
{
    app = a;
	fileDialog = app->get_file_dialog();
    dockLayout = new QHBoxLayout (this);
// 	spacer = new QSpacerItem (QApplication::desktop()->width()- 50, height(),  QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
// 	spacer = new QSpacerItem (40, 20,  QSizePolicy::Expanding, QSizePolicy::Minimum);
//     setLayout (dockLayout);
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
//    // for set category menu on dockbar
//    d_menu_widget = new QWidget(this);
//    // for set dockapp on dockbar
	appWidget = new QWidget();
//    // for set dockicon on dockbar
// 	d_icon_widget = new QWidget(this);
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
//
//    dockLayout->insertWidget(0, lchr);
//    dock_layout->insertWidget(1, d_menu_widget, 1);
//    dock_layout->insertWidget(2, appWidget, 1);
//    dock_layout->insertWidget(3, d_icon_widget, 6); // max stretch factor
//    dock_layout->insertWidget(4, sys, 3);
//    dock_layout->insertWidget(5, clk);
//    dockLayout->insertWidget(1, spacer);
//    dockLayout->insertWidget(1, clk);

	dockLayout->addWidget (lchr);
	dockLayout->addWidget (appWidget);
	dockLayout->addWidget (sys);
	dockLayout->addWidget (clk);

// 	dockLayout->addStretch(1);
//    set_dockmenu(); // at startup, restore category menu on dockbar
	restoreDockApps (); // at startup, restore dockapps on dockbar
	
	setLayout (dockLayout);
	
	show();

}

DockBarTop::~DockBarTop ()
{
	delete rwm;
	delete dockLayout;
	delete app;
// 	delete shortCut;
//    delete icon_layout;
//    delete app_layout;
//    delete menu_layout;
//    delete d_icon;
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

// void DockBarTop::update_dockicon_name(const QString &name, Frame *frm)
// {
//     if (dock_icons.contains(frm->winId())) // if already present
//     {
//         Dockicon *d_icon = dock_icons.value(frm->winId());
//         d_icon->update_name(name);
//     }
// }

// void DockBarTop::add_dockicon(Frame *frm)
// {
//     if (! dock_icons.contains(frm->winId())) // if not already present
//     {
//         d_icon = new Dockicon(frm, sys);
//         dock_icons.insert(frm->winId(), d_icon); // save the Frame winId/Dockicon
//         qDebug() << "Dockicon added to Dockbar. Frame:" << frm->winId();
//         update_dockicon_size();
//         connect(d_icon, SIGNAL(destroy_dockicon(Dockicon *)), this, SLOT(remove_dockicon(Dockicon *))); // delete iconize dockicon and update dockbar size
//     }
// }

// void DockBarTop::remove_dockicon(Dockicon *d_icon) // remove from "Close" right button mouse on Dockbar
// {
//     dock_icons.remove(dock_icons.key(d_icon));
//     qDebug() << "Dockicon remove. Num. after deletion:" << dock_icons.size();
//     d_icon->close();
//     update_dockicon_size();
// }
// 
// void DockBarTop::remove_dockicon(Frame *frm)
// {
//     if (dock_icons.contains(frm->winId())) // remove Dockicon if present
//     {
//         Dockicon *d_icon = dock_icons.value(frm->winId());
//         remove_dockicon(d_icon);
//     }
// }



// void DockBarTop::remove_dockicon(Window win_id) //remove from "Close" cmd on Systray (_NET_SYSTEM_TRAY protocol) if Dockicon is still mapped
// {
//     if (dock_icons.contains(win_id))
//     {
//         Dockicon *d_icon = dock_icons.value(win_id);
//         dock_icons.remove(win_id);
//         qDebug() << "Dockicon remove from Systray cmd. Num. after deletion:" << dock_icons.size();
//         d_icon->close();
//         update_dockicon_size();
//     }
// }

// void DockBarTop::update_dockicon_size()
// {
//     if (! dock_icons.isEmpty())
//     {
//         int num = dock_icons.size();
//         qDebug() << "Dockicon num:" << num;
//         d_length = d_icon_widget->width()/num;
// 
//         if (d_length >= d_icon_widget->width()/3) // max dockicon size = d_icon_widget size/3
//             d_length = d_icon_widget->width()/3;
// 
//         qDebug() << "Dockicon length:" << d_length;
// 
//         foreach(Dockicon *d_icon, dock_icons)
//         {
//             d_icon->setFixedSize(d_length-2, dockHeight-5);
//             icon_layout->addWidget(d_icon);
//         }
//     }
// }

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
    dApp->close();
}
