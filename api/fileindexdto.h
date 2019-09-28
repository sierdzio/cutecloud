#ifndef FILEINDEXDTO_H
#define FILEINDEXDTO_H

#include "endpointdto.h"

class FileIndexDto : public EndpointDto
{
public:
    FileIndexDto();

    QString name() const final;
    QString apiPath() const final;
    QString description() const final;

    static FileIndexDto fromJson(const QByteArray &data);
    QJsonDocument toJson() const final;

    static FileIndexDto fromCbor(const QByteArray &data);
    QCborMap toCbor() const final;
};

#endif // FILEINDEXDTO_H
