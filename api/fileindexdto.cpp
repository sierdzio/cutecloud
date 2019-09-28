#include "fileindexdto.h"

FileIndexDto::FileIndexDto()
{

}

QString FileIndexDto::name() const
{
    return QStringLiteral("FileIndex");
}

QString FileIndexDto::apiPath() const
{
    return EndpointDto::apiPath() + QLatin1String("/fileindex");
}

QString FileIndexDto::description() const
{
    return QStringLiteral("Returns a list of file indexes of the whole cloud "
                          "(for current user), or a requested subset of it");
}

FileIndexDto FileIndexDto::fromJson(const QByteArray &data)
{
    Q_UNUSED(data)

    FileIndexDto result;
    return result;
}

QJsonDocument FileIndexDto::toJson() const
{
    QJsonDocument result;
    // TODO: use Q_ENUM to automatically translate enum name to string
//    QJsonObject object({
//        { fieldString(Field::User), mUser },
//        { fieldString(Field::Directory), mDirectory },
//        });

//        QJsonArray files;
//    for (const auto &info : qAsConst(mFiles)) {
//        const QJsonObject file({
//            { info.fieldString(FileInfo::Name), info.name },
//            { info.fieldString(FileInfo::Created), info.created.toUTC()
//                                                      .toString(Qt::ISODate) },
//            { info.fieldString(FileInfo::Modified), info.modified.toUTC()
//                                                       .toString(Qt::ISODate) },
//            { info.fieldString(FileInfo::Size), QString::number(info.size) },
//            { info.fieldString(FileInfo::IsDirectory), info.isDirectory },
//            });
//        files.append(file);
//    }
//    object.insert(fieldString(Field::Files), files);

//    result.setObject(object);
    return result;
}

FileIndexDto FileIndexDto::fromCbor(const QByteArray &data)
{
    Q_UNUSED(data)

    FileIndexDto result;
    return result;
}

QCborMap FileIndexDto::toCbor() const
{
    QCborMap result;
//    result.insert(Field::User, mUser);
//    result.insert(Field::Directory, mDirectory);

//    QCborArray files;
//    for (const auto &info : qAsConst(mFiles)) {
//        QCborMap file;
//        file.insert(FileInfo::Name, info.name);
//        file.insert(FileInfo::Created, QCborValue(info.created));
//        file.insert(FileInfo::Modified, QCborValue(info.modified));
//        file.insert(FileInfo::Size, info.size);
//        file.insert(FileInfo::IsDirectory, info.isDirectory);
//        files.append(file);
//    }
//    result.insert(Field::Files, files);
    return result;
}
