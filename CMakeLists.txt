#Source: http://www.qtcentre.org/wiki/index.php?title=Compiling_Qt4_apps_with_CMake
# set project's name
PROJECT ( rwm )

# with SET() command you can change variables or define new ones
# here we define SAMPLE_SRCS variable that contains a list of all .cpp files
# note that we don't need \ at the end of line
SET( RWM_SRCS
    ./src/main.cpp 
    ./src/rwm.cpp 
    ./src/frame.cpp 
    ./src/border.cpp 
    ./src/dockbar.cpp 
    ./src/launcher.cpp 
    ./src/dockicon.cpp 
    ./src/desk.cpp 
    ./src/header.cpp 
    ./src/systray.cpp 
    ./src/manager.cpp 
    ./src/filedialog.cpp 
    ./src/colordialog.cpp 
    ./src/colorsel.cpp 
    ./src/msgbox.cpp 
    ./src/runner.cpp 
    ./src/dateclock.cpp 
    ./src/sysicon.cpp 
    ./src/deskapp.cpp 
    ./src/utils.cpp 
    ./src/deskdev.cpp 
    ./src/deskfile.cpp 
    ./src/deskfolder.cpp 
    ./src/dockapp.cpp 
    ./src/trash.cpp 
    ./src/trashdialog.cpp 
    ./src/deskicon.cpp 
    ./src/dockmenu.cpp 
    ./src/settings.cpp 
    ./src/paths.cpp 
    ./src/images.cpp 
    ./src/about.cpp 
    ./src/dockbartop.cpp 
    ./src/xmlparser.cpp 
    ./src/popup.cpp
)

# another list, this time it includes all header files that should be treated with moc
SET( RWM_MOC_HDRS
    ./src/defs.h 
    ./src/rwm.h 
    ./src/frame.h 
    ./src/border.h 
    ./src/dockbar.h 
    ./src/launcher.h 
    ./src/dockicon.h 
    ./src/desk.h 
    ./src/header.h 
    ./src/systray.h 
    ./src/manager.h 
    ./src/filedialog.h 
    ./src/colordialog.h 
    ./src/colorsel.h 
    ./src/msgbox.h 
    ./src/runner.h 
    ./src/sysicon.h 
    ./src/deskapp.h 
    ./src/utils.h 
    ./src/deskdev.h 
    ./src/deskfile.h 
    ./src/deskfolder.h 
    ./src/dockapp.h 
    ./src/trash.h 
    ./src/trashdialog.h 
    ./src/deskicon.h 
    ./src/dockmenu.h 
    ./src/settings.h 
    ./inc/paths.h 
    ./inc/images.h 
    ./inc/about.h 
    ./inc/dockbartop.h 
    ./inc/xmlparser.h 
    ./inc/dateclock.h 
    ./inc/popup.h
)

# some .ui files
SET( RWM_UIS
      ./src/about.ui
)

SET(LANG
    ./language/it_IT.ts 
    ./language/cs_CZ.ts 
    ./language/ru_RU.ts 
    ./language/pl_PL.ts 
    ./language/de_DE.ts 
    ./language/es_ES.ts
  )
# and finally an resource file
# SET( SAMPLE_RCS
#       ./src/rc/sample.qrc
# )

# enable warnings
ADD_DEFINITIONS( -Wall )

# by default only QtCore and QtGui modules are enabled
# other modules must be enabled like this:
# SET( QT_USE_QT3SUPPORT TRUE )   
SET( QT_USE_QTXML TRUE )
SET( QT_USE_DBUS TRUE )

# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
FIND_PACKAGE( Qt4 REQUIRED )

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
INCLUDE( ${QT_USE_FILE} )

# this command will generate rules that will run rcc on all files from SAMPLE_RCS
# in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES( RWM_RC_SRCS ${RWM_RCS} )

# this will run uic on .ui files:
QT4_WRAP_UI( RWM_UI_HDRS ${RWM_UIS} )

# and finally this will run moc:
QT4_WRAP_CPP( RWM_MOC_SRCS ${RWM_MOC_HDRS} )

QT4_AUTOMOC(${RWM_SRCS})

QT4_ADD_TRANSLATION(TRANSLATIONS ${LANG})

# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
# INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR} )
INCLUDE_DIRECTORIES(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

# here we instruct CMake to build "sample" executable from all of the source files
ADD_EXECUTABLE( rwm ${RWM_SRCS} ${RWM_MOC_SRCS} ${RWM_RC_SRCS} ${RWM_UI_HDRS} ${TRANSLATIONS})

# last thing we have to do is to tell CMake what libraries our executable needs,
# luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
TARGET_LINK_LIBRARIES( rwm ${QT_LIBRARIES} )
# target_link_libraries(rwm ${QT_QTCORE_LIBRARY})