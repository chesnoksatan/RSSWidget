#ifndef REQUESTHELPER_H
#define REQUESTHELPER_H

#include <QString>

class RequestHelper
{
public:
    explicit RequestHelper(const QString &address);

public:
    void request() const;

    const QString &getAddress() const { return m_address; }

private:
    const QString m_address;
};

#endif // REQUESTHELPER_H
