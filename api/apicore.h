#ifndef APICORE_H
#define APICORE_H

#include <QStringList>
#include <QHash>

extern QStringList allEndpoints;

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

    static QStringList endpoints();
    static QStringList activeEndpoints();


private:
    static const QStringList mAllEndpoints;
    static const QStringList mActiveEndpoints;
};

#endif // APICORE_H
