/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created: Sat Sep 11 01:22:25 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *info_tab;
    QHBoxLayout *_9;
    QVBoxLayout *_10;
    QLabel *logo;
    QSpacerItem *spacerItem;
    QTextBrowser *info;
    QWidget *contributions_tab;
    QHBoxLayout *_11;
    QVBoxLayout *_12;
    QLabel *contrib_icon;
    QSpacerItem *spacerItem1;
    QTextBrowser *contributions;
    QWidget *translations_tab;
    QHBoxLayout *_13;
    QVBoxLayout *_14;
    QLabel *translators_icon;
    QSpacerItem *spacerItem2;
    QTextBrowser *translators;
    QWidget *license_tab;
    QHBoxLayout *_15;
    QVBoxLayout *_16;
    QLabel *license_icon;
    QSpacerItem *spacerItem3;
    QTextBrowser *license;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(521, 317);
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(About);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        info_tab = new QWidget();
        info_tab->setObjectName(QString::fromUtf8("info_tab"));
        _9 = new QHBoxLayout(info_tab);
#ifndef Q_OS_MAC
        _9->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _9->setContentsMargins(9, 9, 9, 9);
#endif
        _9->setObjectName(QString::fromUtf8("_9"));
        _10 = new QVBoxLayout();
#ifndef Q_OS_MAC
        _10->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _10->setContentsMargins(0, 0, 0, 0);
#endif
        _10->setObjectName(QString::fromUtf8("_10"));
        logo = new QLabel(info_tab);
        logo->setObjectName(QString::fromUtf8("logo"));

        _10->addWidget(logo);

        spacerItem = new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        _10->addItem(spacerItem);


        _9->addLayout(_10);

        info = new QTextBrowser(info_tab);
        info->setObjectName(QString::fromUtf8("info"));
        info->setFrameShape(QFrame::NoFrame);
        info->setFrameShadow(QFrame::Plain);
        info->setOpenExternalLinks(true);

        _9->addWidget(info);

        tabWidget->addTab(info_tab, QString());
        contributions_tab = new QWidget();
        contributions_tab->setObjectName(QString::fromUtf8("contributions_tab"));
        _11 = new QHBoxLayout(contributions_tab);
#ifndef Q_OS_MAC
        _11->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _11->setContentsMargins(9, 9, 9, 9);
#endif
        _11->setObjectName(QString::fromUtf8("_11"));
        _12 = new QVBoxLayout();
#ifndef Q_OS_MAC
        _12->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _12->setContentsMargins(0, 0, 0, 0);
#endif
        _12->setObjectName(QString::fromUtf8("_12"));
        contrib_icon = new QLabel(contributions_tab);
        contrib_icon->setObjectName(QString::fromUtf8("contrib_icon"));

        _12->addWidget(contrib_icon);

        spacerItem1 = new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        _12->addItem(spacerItem1);


        _11->addLayout(_12);

        contributions = new QTextBrowser(contributions_tab);
        contributions->setObjectName(QString::fromUtf8("contributions"));
        contributions->setFrameShape(QFrame::NoFrame);
        contributions->setFrameShadow(QFrame::Plain);
        contributions->setOpenExternalLinks(true);

        _11->addWidget(contributions);

        tabWidget->addTab(contributions_tab, QString());
        translations_tab = new QWidget();
        translations_tab->setObjectName(QString::fromUtf8("translations_tab"));
        _13 = new QHBoxLayout(translations_tab);
#ifndef Q_OS_MAC
        _13->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _13->setContentsMargins(9, 9, 9, 9);
#endif
        _13->setObjectName(QString::fromUtf8("_13"));
        _14 = new QVBoxLayout();
#ifndef Q_OS_MAC
        _14->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _14->setContentsMargins(0, 0, 0, 0);
#endif
        _14->setObjectName(QString::fromUtf8("_14"));
        translators_icon = new QLabel(translations_tab);
        translators_icon->setObjectName(QString::fromUtf8("translators_icon"));

        _14->addWidget(translators_icon);

        spacerItem2 = new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        _14->addItem(spacerItem2);


        _13->addLayout(_14);

        translators = new QTextBrowser(translations_tab);
        translators->setObjectName(QString::fromUtf8("translators"));
        translators->setFrameShape(QFrame::NoFrame);
        translators->setFrameShadow(QFrame::Plain);
        translators->setOpenExternalLinks(true);

        _13->addWidget(translators);

        tabWidget->addTab(translations_tab, QString());
        license_tab = new QWidget();
        license_tab->setObjectName(QString::fromUtf8("license_tab"));
        _15 = new QHBoxLayout(license_tab);
#ifndef Q_OS_MAC
        _15->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _15->setContentsMargins(9, 9, 9, 9);
#endif
        _15->setObjectName(QString::fromUtf8("_15"));
        _16 = new QVBoxLayout();
#ifndef Q_OS_MAC
        _16->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        _16->setContentsMargins(0, 0, 0, 0);
#endif
        _16->setObjectName(QString::fromUtf8("_16"));
        license_icon = new QLabel(license_tab);
        license_icon->setObjectName(QString::fromUtf8("license_icon"));

        _16->addWidget(license_icon);

        spacerItem3 = new QSpacerItem(20, 111, QSizePolicy::Minimum, QSizePolicy::Expanding);

        _16->addItem(spacerItem3);


        _15->addLayout(_16);

        license = new QTextBrowser(license_tab);
        license->setObjectName(QString::fromUtf8("license"));
        license->setFrameShape(QFrame::NoFrame);
        license->setFrameShadow(QFrame::Plain);
        license->setOpenExternalLinks(true);

        _15->addWidget(license);

        tabWidget->addTab(license_tab, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(About);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(About);
        QObject::connect(buttonBox, SIGNAL(accepted()), About, SLOT(accept()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QApplication::translate("About", "About RWM", 0, QApplication::UnicodeUTF8));
        logo->setText(QApplication::translate("About", "icon", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(info_tab), QApplication::translate("About", "&Info", 0, QApplication::UnicodeUTF8));
        contrib_icon->setText(QApplication::translate("About", "icon", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(contributions_tab), QApplication::translate("About", "&Contributions", 0, QApplication::UnicodeUTF8));
        translators_icon->setText(QApplication::translate("About", "icon", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(translations_tab), QApplication::translate("About", "&Translators", 0, QApplication::UnicodeUTF8));
        license_icon->setText(QApplication::translate("About", "icon", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(license_tab), QApplication::translate("About", "&License", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
