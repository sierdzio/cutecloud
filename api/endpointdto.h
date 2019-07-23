#pragma once

#include <QString>
#include <QJsonDocument>
#include <QCborMap>

/*!
 * Base class for all endpoint DTOs (Data Transfer Objects).
 *
 * \note Please remember to register each subclass in apicore.cpp file.
 */
class EndpointDto
{
public:
    virtual ~EndpointDto();

    // Static? So that they can be shown in API summary page?
    virtual QString name() const;
    virtual QString description() const;

    virtual QJsonDocument toJson() const;
    // TODO: use templates?
    //static Endpoint fromJson();
    //static auto fromJson();

    virtual QCborMap toCbor() const;
    // TODO: use templates?
    //static Endpoint fromCbot();
};
