#include "xmlparser.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QDebug>

bool XmlParser::writeXml (const QString  &fileName,
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

//QVariant XmlParser::readXml (const QString &fileName,
//                             const QString &textElem)
//{
//    QString ret;
//    QXmlStreamReader xmlReader;
//    QFile file (fileName);
//    if (!file.open (QFile::ReadOnly | QFile::Text))
//    {
//        qDebug() << "Error: Cannot read file " << qPrintable (fileName)
//                 << ": " << qPrintable(file.errorString());
//        return ":: error: cannot open file";
//    }
//    xmlReader.setDevice (&file);
//    xmlReader.readNext ();

//    while (!xmlReader.atEnd ())
//    {
//        if (xmlReader.isStartElement () && xmlReader.name () == textElem)
//        {
//            qDebug () << "Found " + xmlReader.name ().toString () + " position";
//            ret = xmlReader.readElementText ();
//            qDebug () << "ret:" << ret;
//            break;
//        }
////        else
////            xmlReader.raiseError(QObject::tr("error"));
//        xmlReader.readNext ();
//    }

//    file.close ();
//    if (xmlReader.hasError ())
//    {
//        qDebug() << "Error: Failed to parse file "
//                 << qPrintable (fileName) << ": "
//                 << qPrintable (xmlReader.errorString ());
//        ret = ":: error parsing file";
//    }
//    else if (file.error() != QFile::NoError)
//    {
//        qDebug() << "Error: Cannot read file " << qPrintable (fileName)
//                 << ": " << qPrintable (file.errorString ());
//        ret = ":: error: cannot read file";

//    }

//    return ret;
//}

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
}
