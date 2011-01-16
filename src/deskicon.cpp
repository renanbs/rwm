////////////////////////////////////////
//  File      : deskicon.cpp          //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

#include "../inc/deskicon.h"
#include "../inc/paths.h"

////////////////////////////////////////

Deskicon::Deskicon(Frame *frame, QWidget *parent) : QLabel(parent)
{
    frm = frame;
    grab_pix = QPixmap::grabWindow(frm->winId(), 0, 0, frm->width(), frm->height());
    setPixmap(grab_pix.scaled(frm->width()/4, frm->height()/4, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    setToolTip(frm->cl_name());
    read_settings();
    show();
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(2);
}

Deskicon::~Deskicon()
{
    delete frm;
}

void Deskicon::read_settings()
{
    // get style path
//    QSettings *rwm = new QSettings(QCoreApplication::applicationDirPath() + "/rwm.cfg", QSettings::IniFormat, this);
    QSettings *rwm = new QSettings(Paths::getConfigPath() + "/rwm.cfg", QSettings::IniFormat, this);
    rwm->beginGroup("Style");
    QString stl_name = rwm->value("name").toString();
    QString stl_path = rwm->value("path").toString();
    rwm->endGroup(); //Style
    // get style values
    QSettings *style = new QSettings(stl_path + stl_name, QSettings::IniFormat, this);
    style->beginGroup("Other");
    close_desk_pix = stl_path + style->value("close_dock_pix").toString();
    style->endGroup(); //Other
}

void Deskicon::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        frm->raise_it();
        emit destroy_deskicon(this);
    }
}

void Deskicon::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mousepos = event->pos();
        grabMouse(QCursor(Qt::SizeAllCursor));
    }
    if (event->button() == Qt::RightButton)
    {
        QMenu *menu = new QMenu(this);
        menu->addAction(QIcon(close_desk_pix), tr("Close"));
        menu->popup(event->globalPos());
        connect(menu, SIGNAL(triggered(QAction *)), this, SLOT(run_menu(QAction *)));
    }
}

void Deskicon::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->globalPos()-mousepos;
    move(p.x(), p.y());
}

void Deskicon::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(3);
}

void Deskicon::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(2);
}

void Deskicon::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    releaseMouse();
}

void Deskicon::run_menu(QAction *act)
{
    if (act->text() == tr("Close"))
    {
        emit destroy_deskicon(this);
        frm->destroy_it();
        close();
    }
}
