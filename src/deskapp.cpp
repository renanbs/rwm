////////////////////////////////////////
//  File      : deskapp.cpp           //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

#include "deskapp.h"
#include "../inc/paths.h"

////////////////////////////////////////

Deskapp::Deskapp(const QString &app_nm, const QString &app_exe, const QString &app_pix, QWidget *parent) : QWidget(parent)
{
    setFixedSize(100, 50);
    read_settings();
    app_name = app_nm;
    app_exec = app_exe;
    setToolTip(app_exec + app_name);
    d_app_pix = QPixmap(app_pix);
    zoom = false;
    selected = false;
    show();
}

Deskapp::~Deskapp()
{
    delete rwm;
    delete menu;
}

void Deskapp::read_settings()
{
    // get style path
//    rwm = new QSettings(QCoreApplication::applicationDirPath() + "/rwm.cfg", QSettings::IniFormat, this);
    rwm = new QSettings(Paths::getConfigPath() + "/rwm.cfg", QSettings::IniFormat, this);
    rwm->beginGroup("Style");
    QString stl_name = rwm->value("name").toString();
    QString stl_path = rwm->value("path").toString();
    rwm->endGroup(); //Style
    // get style values
    QSettings *style = new QSettings(stl_path + stl_name, QSettings::IniFormat,this);
    style->beginGroup("Deskapp");
    d_app_col = style->value("name_color").value<QColor>();
    style->endGroup(); //Deskapp
    style->beginGroup("Other");
    delete_link_pix = stl_path + style->value("delete_link_pix").toString();
    style->endGroup(); //Other
}

void Deskapp::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setWindow(-50, -50, 100, 50);
    painter.setPen(d_app_col);
   
    if (selected)
    {
        painter.drawRoundedRect(-50, -50, width(), height(), 5, 5);
    }
    
    QString name = QApplication::fontMetrics().elidedText(app_name, Qt::ElideRight, 90); // if app_name is too long, add ... at the end
   
    painter.setOpacity(0.5);
    painter.setPen(Qt::black);
    painter.drawText(-49, -14, 100, 20, Qt::AlignHCenter, name); // shadow deskapp name
    painter.setOpacity(1);
    painter.setPen(d_app_col);
    painter.drawText(-50, -15, 100, 20, Qt::AlignHCenter, name); // deskapp name
    
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
          
    if (zoom)
    {
        painter.drawPixmap(QRect(-18, -50, 36, 36), d_app_pix, QRect(0, 0, d_app_pix.width(), d_app_pix.height()));// deskapp pix
    }
    else
    {
        painter.drawPixmap(QRect(-16, -50, 32, 32), d_app_pix, QRect(0, 0, d_app_pix.width(), d_app_pix.height()));// deskapp pix
    }
}

void Deskapp::set_selected(bool select)
{
    selected = select;
    update();
}

void Deskapp::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        menu = new QMenu(this);
        QAction *del_app = menu->addAction(QIcon(delete_link_pix), tr("Delete link"));
        menu->popup(event->globalPos());
        connect(del_app, SIGNAL(triggered()), this, SLOT(del_app()));
    }
    if (event->button() == Qt::LeftButton)
    {
        mousepos = event->pos();
        grabMouse(QCursor(Qt::SizeAllCursor));
    }
}

void Deskapp::mouseMoveEvent(QMouseEvent *event)
{
    QPoint p = event->globalPos()-mousepos;
    move(p.x(), p.y());
}

void Deskapp::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    releaseMouse();
    // save new deskapp position on desk writing on Anfico.conf
    rwm->beginGroup("Desktop");
    rwm->beginGroup("App");
    rwm->beginGroup(app_name); // App name
    rwm->setValue("pos", pos());
    rwm->endGroup(); // Icon name
    rwm->endGroup(); // App
    rwm->endGroup(); // Desktop
}

void Deskapp::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QProcess::startDetached(app_exec + app_name); //launch the application
    }
}

void Deskapp::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    zoom = true;
    update();
}

void Deskapp::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    zoom = false;
    update();
}

void Deskapp::del_app()
{
    emit destroy_deskapp(this);
}

QString Deskapp::get_app_name() const
{
    return app_name;
}

void Deskapp::update_style()
{
    read_settings();
    update();
}

