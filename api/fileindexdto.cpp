#include "fileindexdto.h"

//#include <QJsonObject>
#include <QCborArray>

FileIndexDto::FileIndexDto() : EndpointDto()
{
}

FileIndexDto::FileIndexDto(const QString &user, const QString &directory)
    : EndpointDto(), mUser(user), mDirectory(directory)
{
    // Run this once when server starts, then cache the result!
    mIndexes = FileIndex::directory(directory, FileIndex::Mode::MetaDataIndex);
}

FileIndexDto::~FileIndexDto()
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
    result.insert(Field::User, mUser);
    result.insert(Field::Directory, mDirectory);

    QCborArray indexes;
    for (auto i = mIndexes.constBegin(); i != mIndexes.constEnd(); ++i) {
        QCborMap idx;
        const auto index = (*i);
        idx.insert(FileIndex::Path, index.path());
        idx.insert(FileIndex::MetaDataHash, index.metaDataHash());
        idx.insert(FileIndex::DataHash, index.dataHash());
        indexes.append(idx);
    }
    result.insert(Field::Indexes, indexes);
    return result;
}
