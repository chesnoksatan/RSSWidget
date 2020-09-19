#include "XmlParser.h"

#include <QDomDocument>
#include <QDebug>

XmlParser::OutgoingType XmlParser::parse(const QString &incomingData)
{
    OutgoingType outgoingMessage;

    QXmlStreamReader xmlReader(incomingData);

    while ( !(xmlReader.atEnd() || xmlReader.hasError()) )
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if ( token == QXmlStreamReader::StartDocument )
            continue;

        if ( token == QXmlStreamReader::StartElement && xmlReader.name() == Tags.title )
        {
            qDebug() << xmlReader.name() << xmlReader.readElementText();
        }
        if ( token == QXmlStreamReader::StartElement && xmlReader.name() == Tags.creator )
        {
            qDebug() << xmlReader.name() << xmlReader.readElementText();
        }
        if ( token == QXmlStreamReader::StartElement && xmlReader.name() == Tags.pubDate )
        {
            qDebug() << xmlReader.name() << xmlReader.readElementText();
        }
        if ( xmlReader.name() == Tags.description )
        {
            qDebug() << xmlReader.name() << xmlReader.readElementText();
        }
    }

    // TODO: Придумать новую систему
    return outgoingMessage;
}

QString XmlParser::getCommitPubDate(const QString &pubDate)
{

}

QString XmlParser::getCommitAuthor(const QString &author)
{

}

QString XmlParser::getCommitTitle(const QString &description)
{

}

std::map<Commit::FileState, QString> XmlParser::getUpdatedFiles(const QString &description)
{

}

decltype (XmlParser::Tags) XmlParser::Tags;
