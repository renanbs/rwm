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

// Olhar isso
//http://forums.opensuse.org/english/get-help-here/applications/407364-kde-4-images-themes-location.html
//http://techbase.kde.org/Projects/Plasma/Theme#Theme_Location.2C_Structure_and_Definition
//http://sourceforge.net/apps/mediawiki/smplayer/index.php?title=Creating_Themes

// Imagens, temas(imagens dos temas), arquivos de tradução, documentação
//provavelmente vão ficar em /usr/share/rwm, versões default
// Versões do usuário vão ficar em /home/$USER/.rwm/share/
// rwm.cfg e outros arquivos de configuração vão ficar em /home/$USER/.rwm

/*
DIRECTORY STRUCTURE TO FOLLOW:

User theme directory definition:
  $home/USER/.config/rwm/themes: Contain only xml files with the theme description.
  $home/USER/.config/rwm/images: Contain directories with the same name of the xml file theme name.
                        The images for each theme are inside.

Documentation definition:
  $home/USER/.config/rwm/docs/$locale - Contains the documentation to every locale

Translation directory definition:
  $home/USER/.config/rwm/translations: Contains the files with the translations of the system rwm_locale_country.ts


Data definition:
  $home/USER/.config/rwm/config: Several xml files with configuration.
*/

#include "../inc/paths.h"
#include <QLibraryInfo>
#include <QLocale>
#include <QFile>
#include <QRegExp>
#include <QDir>
#include <QFile>
#include <QDebug>

#define DEBUG_PATH

QString Paths::configPath;

QString Paths::getDataPath()
{
    return getConfigPath() + "/general/";
}

QString Paths::getTranslationPath()
{
    return getPath() + "/translations/";
}

QString Paths::getDocPath()
{
    return getPath() + "/docs/";
}

QString Paths::getThemesPath()
{
    return getPath() + "/themes/";
}

QString Paths::getShortcutsPath()
{
    return getPath() + "/shortcuts/";
}

QString Paths::getImagesPath()
{
    return getPath() + "/images/";
}


QString Paths::getConfigPath()
{
	return getPath() + "/config/";
}

QString Paths::getQtTranslationPath()
{
    return QLibraryInfo::location(QLibraryInfo::TranslationsPath);
}

QString Paths::doc(QString file, QString locale)
{
    if (locale.isEmpty())
        locale = QLocale::system().name();

    QString f = getDocPath() + locale + "/" + file;
    qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
    if (QFile::exists(f))
        return f;

    if (locale.indexOf(QRegExp("_[A-Z]+")) != -1)
    {
        locale.replace(QRegExp("_[A-Z]+"), "");
        f = getDocPath() + locale + "/" + file;
        qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
        if (QFile::exists(f))
            return f;
    }

    f = getDocPath() + "en/" + file;
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
//     #ifndef DEBUG_PATH
        if (!configPath.isEmpty())
            return configPath;
        else
            return QDir::homePath() + "/.config/rwm";
//     #else
//         QString path = QDir::homePath() + "/windowManager/rwm-project";
//         return path;
//     #endif
}

bool Paths::findConfigFile (QString filename)
{
	QFile filePathName (getDataPath() + filename);
	if (filePathName.exists())
		return true;
	else
		return false;
}
