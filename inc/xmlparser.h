#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include <QVariant>

class XmlParser
{
    public:
        static bool writeXml     (const QString  &fileName,
                                  const QString  &type,
                                  const QString  &startElem,
                                  const QString  &textElem,
                                  const QVariant &value);
        static QVariant readXml  (const QString  &fileName,
                                  const QString  &type,
                                  const QString  &textElem);

    private:
        static QString filename;

};

#endif // XMLPARSER_H
