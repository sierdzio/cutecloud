#ifndef APICORE_H
#define APICORE_H

#include <QStringList>
#include <QHash>

class ApiCore
{
public:
    static QStringList endpoints();
    static bool registerEndpoint(const QString &name);

private:
    static const QStringList mEndpoints;
};

#endif // APICORE_H
