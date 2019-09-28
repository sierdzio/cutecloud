#ifndef FILEINDEXDTO_H
#define FILEINDEXDTO_H

#include "endpointdto.h"
#include "fileindex.h"

class FileIndexDto : public EndpointDto
{
    Q_GADGET

public:
    // TODO: automatic field registration! (use Q_ENUM, too)
    enum Field {
        User,
        Directory,
        Indexes
    }; Q_ENUM(Field)

    FileIndexDto();

    QString name() const final;
    QString apiPath() const final;
    QString description() const final;

    static FileIndexDto fromJson(const QByteArray &data);
    QJsonDocument toJson() const final;

    static FileIndexDto fromCbor(const QByteArray &data);
    QCborMap toCbor() const final;

private:
    QString mUser;
    QString mDirectory;
    FileList mIndexes;
};

#endif // FILEINDEXDTO_H
