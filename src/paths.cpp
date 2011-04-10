/*
RWM, R Window Manager. A fast QT Desktop Environment / Window Manager.
Copyright (C) 2010-2011 Renan Biegelmeyer <rwindowmanager@gmail.com>

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


// DIRECTORY STRUCTURE TO FOLLOW:
// 
// User theme directory definition:
//   $home/USER/.local/share/rwm/themes: Contains the directory, named the name of the theme with it's images inside
//   /usr/share/rwm/themes/: Contain themes to be shared with all users on the same computer.
//   
// Images definition
//   /usr/share/rwm/images: Contain the images used in the about box.
// 
// Data definition:
//   $home/USER/.config/rwm/config: Several xml files with configuration.
// 
// Documentation definition:
//   /usr/share/rwm/docs/$locale - Contains the documentation to every locale
// 
// Translation directory definition:
//   /usr/share/rwm/translations: Contains the files with the translations of the system rwm_locale_country.ts



#include "../inc/paths.h"
#include <QLibraryInfo>
#include <QLocale>
#include <QFile>
#include <QRegExp>
#include <QDir>
#include <QFile>
#include <QDebug>

#define DEBUG_PATH 1
#define VERSION 0.1alpha

QString Paths::configPath;

QString Paths::getTranslationPath(bool def)
{
#if DEBUG_PATH
	return QDir::homePath() + "/windowManager/rwm-project/translations/";
#else
	if (def)
		return "/usr/share/rwm/translations/";
	else
		return QDir::homePath() + "/.local/share/rwm/translations/";	
#endif
}

QString Paths::getDocPath(bool def)
{
#if DEBUG_PATH
	return QDir::homePath() + "/windowManager/rwm-project/docs/";
#else
	if (def)
		return "/usr/share/rwm/docs/";
	else
		return QDir::homePath() + "/.local/share/rwm/docs/";
#endif
}

QString Paths::getImagesPath(bool def)
{
#if DEBUG_PATH
	return QDir::homePath() + "/windowManager/rwm-project/images/";
#else
	if (def)
		return "/usr/share/rwm/images/";
	else
		return QDir::homePath() + "/.local/share/rwm/images/";
#endif
}

QString Paths::getConfigPath()
{
#if DEBUG_PATH
	return QDir::homePath() + "/windowManager/rwm-project/config/";
#else
	return QDir::homePath() + "/.config/rwm/";
#endif
}

QString Paths::getThemesPath(bool def)
{
#if DEBUG_PATH
	return QDir::homePath() + "/windowManager/rwm-project/themes/";
#else
	if (def)
		return "/usr/share/rwm/themes/";
	else
		return QDir::homePath() + "/.local/share/rwm/themes/";
#endif
}

QString Paths::getQtTranslationPath()
{
	return QLibraryInfo::location(QLibraryInfo::TranslationsPath);
}

QString Paths::doc(QString file, QString locale)
{
	if (locale.isEmpty())
		locale = QLocale::system().name();

	QString f = getDocPath(true) + locale + "/" + file;
	qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
	if (QFile::exists(f))
		return f;

	if (locale.indexOf(QRegExp("_[A-Z]+")) != -1)
	{
		locale.replace(QRegExp("_[A-Z]+"), "");
		f = getDocPath(true) + locale + "/" + file;
		qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
		if (QFile::exists(f))
			return f;
	}

	f = getDocPath(false) + "en/" + file;
	return f;
}

bool Paths::findAndCreateStructurePath()
{
	QString directory = QDir::homePath() + "/.config/rwm";
	QDir dir (directory);
	if (!dir.exists ())
	{
		if (!dir.mkdir (directory))
		{
			qDebug() << "Could not create config .rwm directory!" << endl;
			return false;
		}
        else
		{
			qDebug() << "Config .config/rwm directory created succesfully!" << endl;
			return true;
		}
	}
	else
	{
		qDebug() << dir.homePath() + "/.config/rwm" + " found!" << endl;
		return false;
	}
}

QString Paths::getPath()
{
	if (!configPath.isEmpty())
		return configPath;
	else
		return QDir::homePath() + "/.config/rwm";
}

bool Paths::findConfigFile (QString filename)
{
	QFile filePathName (getConfigPath() + filename);
	if (filePathName.exists())
		return true;
	else
		return false;
}
