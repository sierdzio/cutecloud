#include "endpointdto.h"

EndpointDto::~EndpointDto()
{
}

QString EndpointDto::name() const
{
    return QStringLiteral("Endpoint");
}

QString EndpointDto::description() const
{
    return QStringLiteral("Base class for all endpoints. Does not do anything");
}

QJsonDocument EndpointDto::toJson() const
{
    return QJsonDocument();
}

QCborMap EndpointDto::toCbor() const
{
    return QCborMap();
}
