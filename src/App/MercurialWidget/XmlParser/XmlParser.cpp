#include "XmlParser.h"

#include <QDebug>

XmlParser::OutgoingType XmlParser::parse(const QString &incomingData)
{
    OutgoingType outgoingMessage;

    QDomDocument document;
    document.setContent(incomingData);

    QDomElement root = document.elementsByTagName(Tags.channel).at(0).toElement();
    QDomNode rootNode = root.firstChild();

    while ( !rootNode.isNull() )
    {
        QDomElement elem = rootNode.toElement();
        rootNode = rootNode.nextSibling();

        if ( elem.tagName() == Tags.item )
        {
            QDomNode itemNode = elem.firstChild();
            Commit currentCommit;

            while ( !itemNode.isNull() )
            {
                QDomElement itemElement = itemNode.toElement();

                if ( itemElement.tagName() == Tags.title )
                    currentCommit.setTitle(itemElement.text());

                if ( itemElement.tagName() == Tags.creator )
                    currentCommit.setAuthor(itemElement.text());

                if ( itemElement.tagName() == Tags.pubDate )
                    currentCommit.setTime(getCommitPubDate(itemElement.text()));

                if ( itemElement.tagName() == Tags.description )
                    currentCommit.setUpdatedFiles(getUpdatedFiles(itemElement.text()));

                itemNode = itemNode.nextSibling();
            }
//            qDebug().noquote() << currentCommit.toString() << "\n";
            outgoingMessage.push_back(currentCommit);
        }
    }

    return outgoingMessage;
}

QString XmlParser::getCommitPubDate(const QString &pubDate)
{
    auto date = pubDate;

    date.remove(" -0000");
    date.remove(0, 5);

    return date;
}

XmlParser::UpdatedFiles XmlParser::getUpdatedFiles(QString description)
{
    UpdatedFiles outgoingMessage;

    description.remove(0, description.indexOf("\n\n") + 2);
    description.remove("</pre>");

    auto files = description.split("\n");

    for ( auto &line : files )
    {
        const auto index = line.indexOf("(");

        line.remove(index, line.size() - index);
        line = line.simplified();

        if ( line.at(0) == "M" )
            outgoingMessage.push_back({Commit::FileState::Modified, line.remove(0, 2)});
        if ( line.at(0) == "A" )
            outgoingMessage.push_back({Commit::FileState::Added, line.remove(0, 2)});
        if ( line.at(0) == "R" )
            outgoingMessage.push_back({Commit::FileState::Removed, line.remove(0, 2)});
    }

    return outgoingMessage;
}

QString Commit::toString() const
{
    return "Автор коммита: " + m_commitAuthor +
           "\nДата коммита: " + m_commitTime +
           "\nЗаголовок коммита: " + m_commitTitle;
}

decltype (XmlParser::Tags) XmlParser::Tags;
