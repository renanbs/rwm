#include "../inc/about.h"
#include "ui_about.h"
#include "../inc/paths.h"
#include "../inc/images.h"
#include <QFile>

#define TRANS_LIST


About::About(QWidget * parent, Qt::WindowFlags f)
        : QDialog(parent, f),
        ui(new Ui::About)

{
    ui->setupUi(this);

    ui->logo->setPixmap (Images::icon("logo_about", 64));
    ui->contrib_icon->setPixmap( Images::icon("contributors" ) );
    ui->translators_icon->setPixmap (Images::icon("translators"));
    ui->license_icon->setPixmap (Images::icon("license"));

    ui->info->setText(
        "<b>RWM</b> &copy; 2010-2010 Renan Biegelmeyer &lt;WRITE EMAIL&gt;<br><br>"
        "<b>" + tr("Version: %1").arg("0.1 alpha") + "</b>" +

        "<br>" +
        tr("Using Qt %1 (compiled with Qt %2)").arg(qVersion()).arg(QT_VERSION_STR) + "<br><br>" +
//		mplayer_version +
        tr("Visit our web for updates:") +"<br>"+
        link ("http://code.google.com/p/rwm-project/")
//        + "<br>" +
//        link ("www.GET.A.WEB.SITE")
        + "<br><br>"
    );


    QString license_file = Paths::doc ("gpl.html", (QString)QLocale::English);
    if (QFile::exists (license_file))
    {
        QFont fixed_font;
        fixed_font.setStyleHint (QFont::TypeWriter);
        fixed_font.setFamily ("Courier");
        ui->license->setFont (fixed_font);

        QFile f(license_file);
        if (f.open(QIODevice::ReadOnly))
            ui->license->setText (QString::fromUtf8(f.readAll().constData()));

        f.close();
    }
    else
    {
        ui->license->setText(
        "<i>" +
        tr("This program is free software; you can redistribute it and/or modify "
        "it under the terms of the GNU General Public License as published by "
        "the Free Software Foundation; either version 2 of the License, or "
        "(at your option) any later version.") + "</i>");
    }

    ui->translators->setHtml( getTranslators() );

    ui->contributions->setText(
        tr("RWM logo by %1").arg("Renan Biegelmeyer &lt;WRITE EMAIL&gt;") + "<br><br>" +
        tr("The following people have contributed with patches "
           "(see the changelog for details):") +
        "<pre>" +
        QString(
        "So far, no one has contributed!\n"
        "This about box was stolen from the SMPlayer project!\n"
        ).replace("<", "&lt;").replace(">", "&gt;") +
        "</pre>" +
        tr("If there's any omission, please report.")
    );

    // Copy the background color ("window") of the tab widget to the "base" color of the qtextbrowsers
    // Problem, it doesn't work with some styles, so first we change the "window" color of the tab widgets.
    ui->info_tab->setAutoFillBackground(true);
    ui->contributions_tab->setAutoFillBackground(true);
    ui->translations_tab->setAutoFillBackground(true);

    QPalette pal = ui->info->palette ();
    pal.setColor (QPalette::Window, palette().color(QPalette::Window));

    ui->info->setPalette(pal);
    ui->contributions_tab->setPalette(pal);
    ui->translations_tab->setPalette(pal);
    ui->license_tab->setPalette(pal);


    QPalette p = ui->info->palette();
    //p.setBrush(QPalette::Base, info_tab->palette().window());
    p.setColor(QPalette::Base, ui->info_tab->palette().color(QPalette::Window));

    ui->info->setPalette(p);
    ui->contributions->setPalette(p);
    ui->translators->setPalette(p);

    adjustSize();
}

About::~About()
{
    delete ui;
}

void About::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString About::link(const QString & url, QString name) {
    if (name.isEmpty()) name = url;
    return QString("<a href=\"" + url + "\">" + name +"</a>");
}

QString About::getTranslators() {
        return QString(
                 tr("The following people have contributed with translations:") +
#ifndef TRANS_TABLE
         "<ul>" +
#else
         "<table>" +
#endif
         trad(tr("Brazilian Portuguese"), "Renan Biegelmeyer <WRITE EMAIL>") +
         trad(tr("English"), "Renan Biegelmeyer <WRITE EMAIL>")
         /*+ trad(tr("Slovak"), "Sweto <peter.mendel@gmail.com>") +
                 trad(tr("Italian"), QStringList()
                        << "greengreat <gmeildeno@gmail.com>"
                        << "Giancarlo Scola <scola.giancarlo@libero.it>") +
         trad(tr("French"), QStringList()
                        << "Olivier g <1got@caramail.com>"
                        << "Temet <goondy@free.fr>"
                        << "Erwann MEST <kud.gray@gmail.com>") +
                 trad(tr("Simplified-Chinese"), "Tim Green <iamtimgreen@gmail.com>") +
         trad(tr("Russian"), QString::fromUtf8("????? ???????? <wiselord1983@gmail.com>"))+
         trad(tr("Hungarian"), QStringList()
                        << "Charles Barcza <kbarcza@blackpanther.hu>"
                        << "CyberDragon <cyberdragon777@gmail.com>") +
         trad(tr("Polish"), QStringList()
                        << "qla <qla0@vp.pl>"
                        << "Jarek <ajep9691@wp.pl>" ) +
         trad(tr("Japanese"), "Nardog <nardog@e2umail.com>") +
         trad(tr("Dutch"), QStringList()
                        << "profoX <wesley@ubuntu-nl.org>"
                        << "BalaamsMiracle"
                        << "Kristof Bal <kristof.bal@gmail.com>") +
         trad(tr("Ukrainian"), QStringList()
                        << "Motsyo Gennadi <drool@altlinux.ru>"
                        << "Oleksandr Kovalenko <alx.kovalenko@gmail.com>" ) +
         trad(tr("Portuguese - Brazil"), "Ventura <ventura.barbeiro@terra.com.br>") +
         trad(tr("Georgian"), "George Machitidze <giomac@gmail.com>") +
         trad(tr("Czech"), QStringList()
                        << QString::fromUtf8("Martin Dvo?ák <martin.dvorak@centrum.cz>")
                        << QString::fromUtf8("Jaromír Smr?ek <jaromir.smrcek@zoner.com>") ) +
         trad(tr("Bulgarian"), "<marzeliv@mail.bg>") +
         trad(tr("Turkish"), "alper er <alperer@gmail.com>") +
         trad(tr("Swedish"), "Leif Larsson <leif.larsson@gmail.com>") +
         trad(tr("Serbian"), "Kunalagon Umuhanik <kunalagon@gmail.com>") +
         trad(tr("Traditional Chinese"), "Hoopoe <dai715.tw@yahoo.com.tw>") +
         trad(tr("Romanian"), "DoruH <DoruHushHush@gmail.com>") +
         trad(tr("Portuguese - Portugal"), QStringList()
                        << "Waxman <waxman.pt@gmail.com>"
                        << QString::fromUtf8("Sérgio Marques <smarquespt@gmail.com>") ) +
                trad(tr("Greek"), "my80s <wamy80s@gmail.com>") +
                trad(tr("Finnish"), "peeaivo <peeaivo@gmail.com>") +
                trad(tr("Korean"), "Heesu Yoon <imsu30@gmail.com>") +
                trad(tr("Macedonian"), "Marko Doda <mark0d0da@gmail.com>") +
                trad(tr("Basque"), "Piarres Beobide <pi@beobide.net>") +
                trad(tr("Catalan"), QString::fromUtf8("Roger Calvó <rcalvoi@yahoo.com>")) +
                trad(tr("Slovenian"), "Janez Troha <janez.troha@gmail.com>") +
                trad(tr("Arabic"), "Muhammad Nour Hajj Omar <arabianheart@live.com>") +
                trad(tr("Kurdish"), "Si_murg56 <simurg56@gmail.com>") +
                trad(tr("Galician"), "Miguel Branco <mgl.branco@gmail.com>") +
                trad(tr("Vietnamese"), QString::fromUtf8("Lê Xuân Th?o <thaolx@gmail.com>")) +
                trad(tr("Estonian"), QString::fromUtf8("Olav Mägi <olav.magi@hotmail.com>")) +
                trad(tr("Lithuanian"), "Freemail <ricka_g@freemail.lt>") */+
#ifndef TRANS_TABLE
        "</ul>");
#else
        "</table>");
#endif
}

QString About::trad(const QString & lang, const QString & author) {
        return trad(lang, QStringList() << author);
}

QString About::trad(const QString & lang, const QStringList & authors) {
#ifdef TRANS_ORIG
        QString s;

        switch (authors.count()) {
                case 2: s = tr("%1 and %2"); break;
                case 3: s = tr("%1, %2 and %3"); break;
                case 4: s = tr("%1, %2, %3 and %4"); break;
                case 5: s = tr("%1, %2, %3, %4 and %5"); break;
                default: s = "%1";
        }

        for (int n = 0; n < authors.count(); n++) {
                QString author = authors[n];
                s = s.arg(author.replace("<", "&lt;").replace(">", "&gt;"));
        }

        return "<li>"+ tr("<b>%1</b>: %2").arg(lang).arg(s) + "</li>";
#endif

#ifdef TRANS_LIST
        QString s = "<ul>";;
        for (int n = 0; n < authors.count(); n++) {
                QString author = authors[n];
                s += "<li>"+ author.replace("<", "&lt;").replace(">", "&gt;") + "</li>";
        }
        s+= "</ul>";

        return "<li>"+ tr("<b>%1</b>: %2").arg(lang).arg(s) + "</li>";
#endif

#ifdef TRANS_TABLE
        QString s;
        for (int n = 0; n < authors.count(); n++) {
                QString author = authors[n];
                s += author.replace("<", "&lt;").replace(">", "&gt;");
                if (n < (authors.count()-1)) s += "<br>";
        }

        return QString("<tr><td align=right><b>%1</b></td><td>%2</td></tr>").arg(lang).arg(s);
#endif
}
