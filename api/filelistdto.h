#pragma once

#include "endpointdto.h"

class FileListDto : public EndpointDto
{
public:
    enum Fields {
        User,
        Directory,
        Files
    };

    FileListDto();
    virtual ~FileListDto();

    QString name() const final;
    QString description() const final;

    QJsonDocument toJson() const final;
    QCborMap toCbor() const final;
};
