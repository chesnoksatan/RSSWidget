#pragma once

#include <QDomDocument>

#include <map>

class Commit
{
public:
    enum FileState {
        Modified = 0,
        Added,
        Removed
    };

    using UpdatedFiles =  std::vector<std::pair<FileState, QString>>;
    explicit Commit() {}

private:

    QString m_commitTitle;
    QString m_commitTime;
    QString m_commitAuthor;
    UpdatedFiles m_commitUpdatedFiles;

public:
    void setTitle(const QString &title) { m_commitTitle = title; }
    void setTime(const QString &time) { m_commitTime = time; }
    void setAuthor(const QString &author) { m_commitAuthor = author; }
    void setUpdatedFiles(const UpdatedFiles &updatedFiles) { m_commitUpdatedFiles = updatedFiles; }

    QString getTitle() const { return m_commitTitle; }
    QString getTime() const { return m_commitTime; }
    QString getAuthor() const { return m_commitAuthor; }
    const UpdatedFiles &getUpdatedFiles() const { return m_commitUpdatedFiles; }

    QString toString() const;
};

class XmlParser
{
public:
    using OutgoingType = std::vector<Commit>;
    using UpdatedFiles = std::vector<std::pair<Commit::FileState, QString>>;

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

private:
    static QString getCommitPubDate(const QString &pubDate);
    static UpdatedFiles getUpdatedFiles(QString description);
};
