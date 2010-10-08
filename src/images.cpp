/*
RWM, R Window Manager. A fast QT Desktop Environment / Window Manager.
Copyright (C) 2010-2010 Renan Biegelmeyer <rwindowmanager@gmail.com>

The original class was copied from smplayer.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include "../inc/images.h"
#include "../inc/paths.h"

#include <QFile>


QString Images::filename (const QString & name, bool png)
{
	QString filename = name;

    if (filename.endsWith("_small"))
		filename = filename.replace("_small", "");

	if (png) filename += ".png";

	return filename;
}

//QString Images::file (const QString & icon_name)
//{
//	bool ok = false;
//	QString filename;
//
//    if (!pref->iconset.isEmpty())
//    {
//		filename = Paths::configPath() + "/themes/" + pref->iconset + "/" +  icon_name;
//        if (!QFile::exists(filename))
//        {
//			filename = Paths::themesPath() + "/" + pref->iconset + "/" +  icon_name;
//		}
//
//		ok = (QFile::exists(filename));
//	}
//
//    if (!ok)
//    {
//		filename = ":/icons-png/" + icon_name;
//	}
//
//	qDebug("Images::file: icon_name: '%s', filename: '%s'", icon_name.toUtf8().constData(), filename.toUtf8().constData());
//
//	return filename;
//}

QPixmap Images::loadIcon(const QString & icon_name)
{
	QPixmap p;

    QString filename = Paths::getThemesPath () + icon_name;
    if (!QFile::exists (filename))
    {
		filename = Paths::getImagesPath() + icon_name;
		p.load( filename );
    }
	else
		p.load( filename );

    return p;
}

QPixmap Images::icon (QString name, int size, bool png)
{
    bool small = false;

    if (name.endsWith("_small"))
        small = true;

    QString icon_name = Images::filename (name, png);

    QPixmap p = Images::loadIcon ( icon_name );
    bool ok = !p.isNull();

    if (!ok)
    {
        p = QPixmap(":/images/" + icon_name);
        ok = !p.isNull();
    }

    if (ok)
    {
        if (small)
            p = resize(&p);

        if (size!=-1)
            p = resize(&p,size);
    }
    else
		qWarning("Images2::icon: icon '%s' not found", name.toUtf8().data());

    return p;
}

QPixmap Images::resize(QPixmap *p, int size)
{
	return QPixmap::fromImage( (*p).toImage().scaled(size,size,Qt::IgnoreAspectRatio,Qt::SmoothTransformation) );
}

QPixmap Images::flip(QPixmap *p)
{
	return QPixmap::fromImage( (*p).toImage().mirrored(true, false) );
}

QPixmap Images::flippedIcon(QString name, int size, bool png)
{
	QPixmap p = icon(name, size, png);
	p = flip(&p);
	return p;
}

QString Images::readThemeName()
{
	//read theme name using xmlParser class
	return 0;
}
