#ifndef POPUP_H
#define POPUP_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QTextEdit;
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
};
//! [0]



#endif // POPUP_H
