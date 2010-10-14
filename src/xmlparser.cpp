#include "xmlparser.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QDomElement>
#include <QDomDocument>

/**
*   @brief This is the old writeXml method
*/
bool XmlParser::writeXml    (const QString  &fileName,
							 const QString  &type,
							 const QString  &startElem,
							 const QString  &textElem,
							 const QVariant &value)
{
    QFile file (fileName);
    if (!file.open (QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Error: Cannot write file " << qPrintable (fileName) << ": " << qPrintable (file.errorString ());
        return false;
    }
    QString valor = value.toString();
    QXmlStreamWriter xmlWriter (&file);
    xmlWriter.setAutoFormatting (true);
    xmlWriter.writeStartDocument ();
    xmlWriter.writeStartElement (type);
    xmlWriter.writeStartElement (startElem);
    xmlWriter.writeTextElement (textElem, valor);
    xmlWriter.writeEndDocument ();
    file.close ();
    if (file.error ())
    {
        qDebug() << "Error: Cannot write file " << qPrintable (fileName) << ": " << qPrintable (file.errorString ());
        return false;
    }
        return true;
}

bool XmlParser::writeXml (const QString  &fileName,
						  const QString  &type,
						  const QString  &startElem,
						  const QString  &subElem,
						  const QString  &propX,
						  const QString  &x,
						  const QString  &propY,
						  const QString  &y)
{
	QFile file (fileName);
	if (!file.open (QFile::WriteOnly | QFile::Text))
	{
		qDebug() << "Error: Cannot write file " << qPrintable (fileName) << ": " << qPrintable (file.errorString ());
		return false;
	}
	QXmlStreamWriter xmlWriter (&file);
	xmlWriter.setAutoFormatting (true);
	xmlWriter.writeStartDocument ();
	xmlWriter.writeStartElement (type);
	xmlWriter.writeStartElement (startElem);
	xmlWriter.writeStartElement (subElem);
	xmlWriter.writeTextElement (propX, x);
	xmlWriter.writeTextElement (propY, y);
	xmlWriter.writeEndDocument ();
	file.close ();
	if (file.error ())
	{
		qDebug() << "Error: Cannot write file " << qPrintable (fileName) << ": " << qPrintable (file.errorString ());
		return false;
	}
		return true;
}

QVariant XmlParser::readXml (const QString &fileName,
                             const QString &type,
                             const QString &textElem)
{
    QString ret;
    QXmlStreamReader xmlReader;
    QFile file (fileName);
    if (!file.open (QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error: Cannot read file " << qPrintable (fileName)
                 << ": " << qPrintable(file.errorString());
        return ":: error: cannot open file";
    }
    xmlReader.setDevice (&file);
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader.readNext ();
        // If token is just StartDocument, we'll go to next.
        if (token == QXmlStreamReader::StartDocument)
            continue;

        // If token is StartElement, we'll see if we can read it.
        if (token == QXmlStreamReader::StartElement)
        {
            // If it's named persons, we'll go to the next.
            if(xmlReader.name() == type)
                continue;
            // If it's named person, we'll dig the information from there.
            if(xmlReader.name() == textElem)
            {
                ret = xmlReader.readElementText ();
                return ret;
            }
        }
    }
    // Error handling.
    if(xmlReader.hasError())
    {
        qDebug() << "Error: Failed to parse file "
				 << qPrintable (fileName) << ": "
				 << qPrintable (xmlReader.errorString ());
    }
    xmlReader.clear();

    return 0;
}

QVariant XmlParser::readXml (const QString &fileName,
							 const QString &type,
							 const QString &textElem,
							 const QString &propr)
{
	QString ret;
	QXmlStreamReader xmlReader;
	QFile file (fileName);
	if (!file.open (QFile::ReadOnly | QFile::Text))
	{
		qDebug() << "Error: Cannot read file " << qPrintable (fileName)
				 << ": " << qPrintable(file.errorString());
		return ":: error: cannot open file";
	}
	xmlReader.setDevice (&file);
	while(!xmlReader.atEnd() && !xmlReader.hasError())
	{
		// Read next element
		QXmlStreamReader::TokenType token = xmlReader.readNext ();
		// If token is just StartDocument, we'll go to next.
		if (token == QXmlStreamReader::StartDocument)
			continue;

		// If token is StartElement, we'll see if we can read it.
		if (token == QXmlStreamReader::StartElement)
		{
			// If it is "type", we'll go to the next.
			if(xmlReader.name() == type)
				continue;
			// If it's textElem, we'll go to the next.
			if(xmlReader.name() == textElem)
				continue;
			// If it's propr, we'll dig the information from there.
			if(xmlReader.name() == propr)
			{
				ret = xmlReader.readElementText ();
				return ret;
			}
		}
	}
	// Error handling.
	if(xmlReader.hasError())
	{
		qDebug() << "Error: Failed to parse file "
				 << qPrintable (fileName) << ": "
				 << qPrintable (xmlReader.errorString ());
	}
	xmlReader.clear();

	return 0;
}

bool XmlParser::updateXml  (const QString &fileName,
							const QString &type, //desktop
							const QString &startElem, //trash
							const QString &subElem, //pos
							const QString &propr,	//x
							const QString &value)
{
	QFile inputFile (fileName);
	if (!inputFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
	{
		qDebug() << "Failed to open file for reading.";
		return false;
	}

	QDomDocument document;
	if (!document.setContent (&inputFile))
	{
		qDebug() << "Failed to parse the file into a DOM tree.";
		inputFile.close();
		return false;
	}

	inputFile.close();

	QDomElement system  = document.firstChildElement (type);
	QDomElement startEl = system.firstChildElement (startElem);
	QDomElement sub     = startEl.firstChildElement (subElem);
	QDomElement prop    = sub.firstChildElement (propr);
//	qWarning() << prop.text() << prop.childNodes().count();

	QDomText val = document.createTextNode(value);
	prop.replaceChild(val, prop.firstChild());
//	qWarning() << prop.text() << prop.childNodes().count();

	QFile outputFile (fileName);
	if (!outputFile.open (QIODevice::WriteOnly | QIODevice::Text))
	{
		qDebug() << "Failed to open file for writing.";
		return false;
	}

	QTextStream stream (&outputFile);
	stream << document.toString();

	outputFile.close();

	return true;
}
