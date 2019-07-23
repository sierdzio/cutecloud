#ifndef APICORE_H
#define APICORE_H

#include <QStringList>
#include <QHash>

class ApiCore
{
public:
    /*!
     * All endpoints available in Cutecloud.
     *
     * If some endpoints are disabled server configuration (see EndpointConfig),
     * the list of active endpoints can be accessed in endpoints() and
     * activeEndpoints() methods.
     */
    static QStringList allEndpoints();

    QStringList endpoints() const;
    QStringList activeEndpoints() const;


private:
    static const QStringList mAllEndpoints;
    const QStringList mActiveEndpoints;
};

#endif // APICORE_H
