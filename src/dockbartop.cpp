#include "../inc/dockbartop.h"
#include "../inc/paths.h"
#include "defs.h"

DockBarTop::DockBarTop (Rwm *a, QWidget *parent) : QLabel(parent)
{
    app = a;
//    file_dialog = app->get_file_dialog();
    dockLayout = new QHBoxLayout (this);
    setLayout (dockLayout);
    dockLayout->setContentsMargins (0, 0, 0, 0);
    dockLayout->setSpacing (1);
    dockLayout->setSizeConstraint (QLayout::SetNoConstraint);
    setAcceptDrops (true); // for drag and drop from Filedialog
    setAttribute (Qt::WA_AlwaysShowToolTips);
    readSettings ();
//    init();

    setGeometryDockTop();

    // add launcher to dockbar
//    lchr = new Launcher(a, this);
//    lchr->setFixedSize(dock_height-1, dock_height-1);
//    // for set category menu on dockbar
//    d_menu_widget = new QWidget(this);
//    // for set dockapp on dockbar
//    d_app_widget = new QWidget(this);
//    // for set dockicon on dockbar
//    d_icon_widget = new QWidget(this);
//    // add systray to dockbar
//    sys = new Systray(this);
//    // add clock to dockbar
//    clk = new Dateclock(this);
//    clk->setFixedSize(dock_height*2, dock_height-1);

//    menu_layout = new QHBoxLayout();
//    d_menu_widget->setLayout(menu_layout);
//    menu_layout->setAlignment(Qt::AlignLeft);
//    menu_layout->setContentsMargins(0, 0, 0, 0);
//    menu_layout->setSpacing(1);
//
//    icon_layout = new QHBoxLayout();
//    d_icon_widget->setLayout(icon_layout);
//    icon_layout->setAlignment(Qt::AlignLeft);
//    icon_layout->setContentsMargins(5, 0, 5, 0);
//    icon_layout->setSpacing(1);
//
//    app_layout = new QHBoxLayout();
//    d_app_widget->setLayout(app_layout);
//    app_layout->setAlignment(Qt::AlignLeft);
//    app_layout->setContentsMargins(5, 0, 5, 0);
//    app_layout->setSpacing(1);
//
//    dock_layout->insertWidget(0, lchr);
//    dock_layout->insertWidget(1, d_menu_widget, 1);
//    dock_layout->insertWidget(2, d_app_widget, 1);
//    dock_layout->insertWidget(3, d_icon_widget, 6); // max stretch factor
//    dock_layout->insertWidget(4, sys, 3);
//    dock_layout->insertWidget(5, clk);
//
//    set_dockmenu(); // at startup, restore category menu on dockbar
//    set_dockapp(); // at startup, restore dockapps on dockbar

    show();

}

DockBarTop::~DockBarTop ()
{
    delete rwm;
    delete dockLayout;
//    delete icon_layout;
//    delete app_layout;
//    delete menu_layout;
//    delete d_icon;
//    delete clk;
//    delete app;
//    delete file_dialog;
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
   // app_link_pix = stl_path + style->value ("app_link_pix").toString();
    styleDockTop->endGroup (); //Other
}
