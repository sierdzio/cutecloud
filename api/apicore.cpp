#include "apicore.h"

#include <QDebug>

#define TYPE_NAME(Type) #Type

const QStringList ApiCore::mAllEndpoints = {
    TYPE_NAME(Endpoint),
    TYPE_NAME(FileList),
    TYPE_NAME(FileIndex)
};

QStringList ApiCore::allEndpoints()
{
    return mAllEndpoints;
}

QStringList ApiCore::endpoints() const
{
    return activeEndpoints();
}

QStringList ApiCore::activeEndpoints() const
{
    // TODO: check active endpoints in EndpointConfig.
    return mActiveEndpoints;
}
