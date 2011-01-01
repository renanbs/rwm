#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include <QVariant>

class XmlParser
{
    public:
		static bool writeXml	 (const QString  &fileName,
                                  const QString  &type,
                                  const QString  &startElem,
                                  const QString  &textElem,
                                  const QVariant &value);
		static bool writeXml     (const QString  &fileName,
								  const QString  &type,
								  const QString  &startElem,
								  const QString  &subElem,
								  const QString  &propX,
								  const QString  &x,
								  const QString  &propY,
								  const QString  &y);

        static QVariant readXml  (const QString  &fileName,
                                  const QString  &type,
                                  const QString  &textElem);

		static QVariant readXml  (const QString &fileName,
								  const QString &type,
								  const QString &textElem,
								  const QString &propr);

		static bool updateXml	 (const QString  &fileName,
								  const QString  &type,
								  const QString  &startElem,
								  const QString  &subElem,
								  const QString  &propr,
								  const QString  &value);

    private:
        static QString filename;

};

#endif // XMLPARSER_H
