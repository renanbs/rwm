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

#ifndef _PATHS_H_
#define _PATHS_H_

#include <QString>

class Paths
{

    public:

        static QString getDataPath();
        static QString getTranslationPath();
        static QString getDocPath();
        static QString getThemesPath();
        static QString getShortcutsPath();
        static QString getQtTranslationPath();
        static QString doc(QString file, QString locale = QString::null);

        //!  Tries to find the path where rwm shoud save it's configuration files,
        //! if it doesn't exist, create the directory structure
        static bool findAndCreateStructurePath();

        //! Return the path where rwm should save its config files
        static QString getConfigPath();
		
		//! Return the path where everything is
		static QString getPath();

        //! Return the path where rwm should find some image files
        static QString getImagesPath();

		static bool findConfigFile (QString filename);

    private:
        static QString configPath;
};

#endif
