#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
    class About;
}

class About : public QDialog {
    Q_OBJECT
public:
    About( QWidget * parent = 0, Qt::WindowFlags f = 0 );
    ~About();

protected:
    void changeEvent(QEvent *e);
    QString link(const QString & url, QString name = "");

    QString getTranslators();

    //! Return a formatted string with the translator and language
    QString trad(const QString & lang, const QString & author);

    QString trad(const QString & lang, const QStringList & authors);

private:
    Ui::About *ui;
};

#endif // ABOUT_H
