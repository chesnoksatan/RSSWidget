#pragma once

#include <QXmlReader>
#include <QMap>

class XmlParser
{
    using OutgoingType = QMap<QString, QString>;
public:
    XmlParser() {}

    static OutgoingType parse(const QString &incomingData);
};
