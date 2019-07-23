#include "apicore.h"

#include <QDebug>

#define TYPE_NAME(Type) #Type

const QStringList ApiCore::mAllEndpoints = {
    TYPE_NAME(Endpoint),
    TYPE_NAME(FileList)
};

QStringList ApiCore::allEndpoints()
{
    return mAllEndpoints;
}

QStringList ApiCore::endpoints()
{
    return activeEndpoints();
}

QStringList ApiCore::activeEndpoints()
{
    // TODO: check active endpoints in EndpointConfig.
    return mActiveEndpoints;
}
