#include <QtGui>
#include "../inc/popup.h"

PopupWindow::PopupWindow(QWidget *parent)
    : QWidget(parent)
{
//    textEdit = new QTextEdit;
//    textEdit->setReadOnly(true);
//    textEdit->setLineWrapMode(QTextEdit::NoWrap);

    msgs = new QLabel;


    QDate date = QDate::currentDate();
    QString stringDate = date.toString("dddd, dd MMMM yyyy");
    msgs->setText(stringDate);

    closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(msgs);
    layout->addWidget(closeButton);
    setLayout(layout);

//    setWindowTitle(tr("Preview"));
}

void PopupWindow::setWindowFlags(Qt::WindowFlags flags)
{
    QWidget::setWindowFlags(flags);
}


