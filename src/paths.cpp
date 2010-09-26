/*  smplayer, GUI front-end for mplayer.
    Copyright (C) 2006-2010 Ricardo Villalba <rvm@escomposlinux.org>

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

#include "../inc/paths.h"
#include <QLibraryInfo>
#include <QLocale>
#include <QFile>
#include <QRegExp>
#include <QDir>
#include <QDebug>

// Olhar isso
//http://forums.opensuse.org/english/get-help-here/applications/407364-kde-4-images-themes-location.html
//http://techbase.kde.org/Projects/Plasma/Theme#Theme_Location.2C_Structure_and_Definition
//http://sourceforge.net/apps/mediawiki/smplayer/index.php?title=Creating_Themes

// Imagens, temas(imagens dos temas), arquivos de tradução, documentação
//provavelmente vão ficar em /usr/share/rwm, versões default
// Versões do usuário vão ficar em /home/$USER/.rwm/share/
// rwm.cfg e outros arquivos de configuração vão ficar em /home/$USER/.rwm
#define DEBUG_PATH

QString Paths::configPath;

QString Paths::getDataPath()
{
    return getConfigPath();
}

QString Paths::getTranslationPath()
{
    return getConfigPath() + "/translations";
}

QString Paths::getDocPath()
{
    return getConfigPath() + "/docs";
}

QString Paths::getThemesPath()
{
    return getConfigPath() + "/themes";
}

QString Paths::getShortcutsPath()
{
    return getConfigPath() + "/shortcuts";
}

QString Paths::getQtTranslationPath()
{
    return QLibraryInfo::location(QLibraryInfo::TranslationsPath);
}

QString Paths::doc(QString file, QString locale)
{
    if (locale.isEmpty())
        locale = QLocale::system().name();

    QString f = getDocPath() + "/" + locale + "/" + file;
    qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
    if (QFile::exists(f))
        return f;

    if (locale.indexOf(QRegExp("_[A-Z]+")) != -1)
    {
        locale.replace(QRegExp("_[A-Z]+"), "");
        f = getDocPath() + "/" + locale + "/" + file;
        qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
        if (QFile::exists(f))
            return f;
    }

    f = getDocPath() + "/en/" + file;
    return f;
}

void Paths::setConfigPath()
{
    QString directory = QDir::homePath() + "/.rwm";
    QDir dir(directory);
    if (!dir.exists())
    {
        if (!dir.mkdir(directory))
            qDebug() << "Could not create config .rwm directory!" << endl;
        else
        {
            qDebug() << "Config .rwm directory created succesfully!" << endl;
            configPath = directory;
        }
    }
    else
    {
        qDebug() << dir.homePath() + "/.rwm" + " found!" << endl;
        configPath = directory;
    }
}

QString Paths::getConfigPath()
{
    #ifndef DEBUG_PATH
        if (!configPath.isEmpty())
            return configPath;
        else
            return QDir::homePath() + "/.rwm";
    #else
        QString path = QDir::homePath() + "/windowManager/rwm-project";
        return path;
    #endif
}

QString Paths::getImagesPath()
{
    #ifndef DEBUG_PATH
        if (!configPath.isEmpty())
            return configPath;
        else
            return QDir::homePath() + "/.rwm";
    #else
        QString path = QDir::homePath() + "/windowManager/rwm-project";
        return path;
    #endif
}

//QString Paths::doc(QString file, QString locale)
//{
//    if (locale.isEmpty())
//        locale = QLocale::system().name();


//    QString f = getDocPath() + "/" + locale + "/" + file;
//    qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
//    if (QFile::exists(f)) return f;

//    if (locale.indexOf(QRegExp("_[A-Z]+")) != -1) {
//        locale.replace(QRegExp("_[A-Z]+"), "");
//        f = getDocPath() + "/" + locale + "/" + file;
//        qDebug("Helper:doc: checking '%s'", f.toUtf8().data());
//        if (QFile::exists(f)) return f;
//    }

//    f = getDocPath() + "/en/" + file;
//    return f;
//}
