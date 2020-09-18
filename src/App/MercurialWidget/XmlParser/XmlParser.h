#pragma once

#include <QXmlStreamReader>
#include <QMap>

class XmlParser
{
    using OutgoingType = QMap<QString, QString>;
public:
    XmlParser() {}

    static OutgoingType parse(const QString &incomingData);

private:

    static const struct
    {
        QString rss = "rss";
        QString channel = "channel";
        QString title = "title";
        QString link = "link";
        QString description = "description";
        QString language = "language";
        QString lastBuildDate = "lastBuildDate";
        QString item = "item";
        QString creator ="dc:creator";
        QString pubDate = "pubDate";
    } Tags;
};
