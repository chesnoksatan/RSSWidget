#include "XmlParser.h"
XmlParser::OutgoingType XmlParser::parse(const QString &incomingData)
{
    OutgoingType outgoingMessage;

    QXmlStreamReader reader(incomingData);

    // TODO: Посмотреть, можно ли переопределить  метод readElementText()
    if ( reader.readNextStartElement() )
    {
        if ( reader.name() == Tags.rss )
        {
            if ( reader.readNextStartElement() )
            {
                if ( reader.name() == Tags.channel )
                {
                    while( reader.readNextStartElement() )
                    {
                         if(reader.name() == Tags.title)
                         {
                             outgoingMessage.insert("Заголовок", reader.readElementText());
                             reader.readNext();
                         }
                         if ( reader.name() == Tags.description )
                         {
                             outgoingMessage.insert("Описание", reader.readElementText());
                             reader.readNext();
                         }
                         if ( reader.name() == Tags.lastBuildDate )
                         {
                             outgoingMessage.insert("Время последнего запроса", reader.readElementText());
                             reader.readNext();
                         }
                         if ( reader.name() == Tags.item )
                         {
                             while ( reader.readNextStartElement() )
                             {
                                 if ( reader.name() == Tags.title )
                                 {
                                     outgoingMessage.insert("Название коммита", reader.readElementText());
                                     reader.readNext();
                                 }
                                 if ( reader.name() == Tags.creator )
                                 {
                                     outgoingMessage.insert("Автор коммита", reader.readElementText());
                                     reader.readNext();
                                 }
                                 if ( reader.name() == Tags.pubDate )
                                 {
                                     outgoingMessage.insert("Дата и время коммита", reader.readElementText());
                                     reader.readNext();
                                 }
                                 if ( reader.name() == Tags.description )
                                 {
                                     outgoingMessage.insert("Изменения", reader.readElementText());
                                     reader.readNext();
                                 }
                                 reader.skipCurrentElement();
                             }
                         }
                         reader.skipCurrentElement();
                    }
                }
            }
        }
    }

    return outgoingMessage;
}

decltype (XmlParser::Tags) XmlParser::Tags;
