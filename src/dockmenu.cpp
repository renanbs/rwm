////////////////////////////////////////
// File : dockmenu.cpp                //
// Written by: g_cigala@virgilio.it   //
// Copyright : GPL                    //
////////////////////////////////////////

#include "../inc/dockmenu.h"
#include "../inc/paths.h"

////////////////////////////////////////

Dockmenu::Dockmenu(QMenu *menu, QWidget *parent) : QWidget(parent)
{
    cat_menu = menu;
    bdr_width = 1;
    zoom = false;
    setToolTip(cat_menu->title());
    read_settings();
}

Dockmenu::~Dockmenu()
{
    delete cat_menu;
}

void Dockmenu::read_settings()
{
    // get style path
    QSettings *rwm = new QSettings(Paths::getConfigPath() + "rwm.cfg", QSettings::IniFormat, this);
    rwm->beginGroup("Style");
    QString stl_name = rwm->value("name").toString();
    QString stl_path = rwm->value("path").toString();
    rwm->endGroup(); //Style
    // get style values
    QSettings *style = new QSettings(stl_path + stl_name, QSettings::IniFormat, this);
    style->beginGroup("Dockicon");
    d_menu_pix = stl_path + style->value("d_icon_pix").toString();
    title_color = style->value("title_color").value<QColor>();
    style->endGroup(); //Dockicon
    style->beginGroup("Dockbar");
    dock_position = style->value("dock_position").toInt();
    style->endGroup(); //Dockbar
    back_pix = QPixmap(d_menu_pix);
    cat_pix = cat_menu->icon().pixmap(width(), height());
}

void Dockmenu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(title_color, bdr_width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawRoundedRect(0, 0, width(), height(), 5, 5);
    painter.drawPixmap(QRect(0, 0, width(), height()), back_pix, QRect(0, 0, back_pix.width(), back_pix.height()));// dock pixmap
    
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    if (zoom)
    {
        painter.drawPixmap(QRect(1, 1, height()-2, height()-2), cat_pix, QRect(0, 0, cat_pix.width(), cat_pix.height()));// category icon
    }
    else
    {
        painter.drawPixmap(QRect(3, 3, height()-6, height()-6), cat_pix, QRect(0, 0, cat_pix.width(), cat_pix.height()));// category icon
    }
}

void Dockmenu::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QPoint p = mapToGlobal(QPoint(0, 0));
        
        if (dock_position == 0) // 0 = bottom / 1 = top
            p.setY(p.y()-cat_menu->sizeHint().height());
        else
            p.setY(p.y()+height());
            
        cat_menu->popup(p);
    }
}

void Dockmenu::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    zoom = true;
    update();
}

void Dockmenu::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    zoom = false;
    update();
}

void Dockmenu::update_style()
{
    read_settings();
    update();
}
