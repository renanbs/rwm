#ifndef POPUP_H
#define POPUP_H

#include <QWidget>
#include <QDate>


QT_BEGIN_NAMESPACE
class QPushButton;
class QTextEdit;
class QLabel;
QT_END_NAMESPACE

//! [0]
class PopupWindow : public QWidget
{
    Q_OBJECT

public:
    PopupWindow(QWidget *parent = 0);

    void setWindowFlags(Qt::WindowFlags flags);

private:
    QTextEdit *textEdit;
    QPushButton *closeButton;
    QLabel *msgs;
};
//! [0]



#endif // POPUP_H
