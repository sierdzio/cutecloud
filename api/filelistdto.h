#pragma once

#include "endpoint.h"

class FileListDto : public EndpointDto
{
public:
    FileListDto();
    virtual ~FileListDto();

    QString name() const final;
    QString description() const final;

    QJsonDocument toJson() const final;
    QCborMap toCbor() const final;
};
