#pragma once

#include <QXmlStreamReader>
#include <QMap>

#include <map>

class Commit
{
public:
    Commit() {}

    enum FileState {
        Modified = 0,
        Added,
        Removed
    };

    void setTitle(const QString &title) { m_commitTitle = title; }
    void setTime(const QString &time) { m_commitTime = time; }
    void setAuthor(const QString &author) { m_commitAuthor = author; }
    void appendFile(const FileState state, const QString &filePath) { m_commitUpdatedFiles.insert({state, filePath}); }

    QString getTitle() const { return m_commitTitle; }
    QString getTime() const { return m_commitTime; }
    QString getAuthor() const { return m_commitAuthor; }
    const std::map<FileState, QString> &getUpdatedFiles() const { return m_commitUpdatedFiles; }

private:
    QString m_commitTitle;
    QString m_commitTime;
    QString m_commitAuthor;
    std::map<FileState, QString> m_commitUpdatedFiles;
};

class XmlParser
{
    // TODO: Придумать новую систему
    using OutgoingType = QMap<QString, QString>;
public:
    XmlParser() {}

    // TODO: Придумать новую систему
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

private:
    static QString getCommitPubDate(const QString &pubDate);
    static QString getCommitAuthor(const QString &author);
    static QString getCommitTitle(const QString &title);
    static std::map<Commit::FileState, QString> getUpdatedFiles(const QString &description);
};
