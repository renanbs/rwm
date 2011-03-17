////////////////////////////////////////
//  File      : main.cpp              //
//  Written by: g_cigala@virgilio.it  //
//  Copyright : GPL                   //
////////////////////////////////////////

#include "../inc/defs.h"
#include "../inc/rwm.h"
#include "../inc/about.h"
////////////////////////////////////////


int main(int argc, char **argv)
{
    Rwm a(argc, argv);
    XSelectInput(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()), KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
                 KeymapStateMask | ButtonMotionMask | PointerMotionMask | EnterWindowMask | LeaveWindowMask | FocusChangeMask | VisibilityChangeMask |
                 ExposureMask | StructureNotifyMask | SubstructureRedirectMask | SubstructureNotifyMask);

    XClearWindow(QX11Info::display(), QX11Info::appRootWindow(QX11Info::appScreen()));
    XSync(QX11Info::display(), False);
    
    QTranslator translator;
    qDebug() << "Language:" << QLocale::system().name();
	QString p = Paths::getTranslationPath();
//     translator.load(QLocale::system().name(), QCoreApplication::applicationDirPath() + "/language/");
	translator.load(QLocale::system().name(), p);
    a.installTranslator(&translator);
    
    qDebug() << "GUI creation...";
    a.create_gui();
    
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}

