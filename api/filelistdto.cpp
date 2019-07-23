#include "filelistdto.h"
#include "apicore.h"

#include <QJsonObject>

#include <QDebug>

FileListDto::FileListDto() : EndpointDto() {
    qDebug() << "FileList!";
}

FileListDto::~FileListDto()
{
}

QString FileListDto::name() const
{
    return QStringLiteral("FileList");
}

QString FileListDto::description() const
{
    return QStringLiteral("Returns a list of files in a particular folder in "
                          "the cloud");
}

QJsonDocument FileListDto::toJson() const
{
    QJsonDocument result;
    const QJsonObject object({
        { "name", name() },
        { "description", description() },
    });
    result.setObject(object);
    return result;
}

QCborMap FileListDto::toCbor() const
{
    return QCborMap();
}
