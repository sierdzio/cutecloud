#include "filelistdto.h"
#include "apicore.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QCborArray>
#include <QCborValue>

#include <QMetaEnum>

#include <QDebug>

// FileInfo
FileInfo::FileInfo()
{
}

FileInfo::FileInfo(const QFileInfo &info)
{
    name = info.fileName();
    created = info.birthTime();
    modified = info.lastModified();
    size = info.size();
    isDirectory = info.isDir();
}

QByteArray FileInfo::fieldString(const FileInfo::Field field)
{
    const QMetaEnum metaEnum = QMetaEnum::fromType<FileInfo::Field>();
    return metaEnum.valueToKey(int(field));
}

// FileInfoList
FileInfoList::FileInfoList(const QFileInfoList &list)
{
    for (const auto &info : list) {
        append(FileInfo(info));
    }
}


// FileListDto
FileListDto::FileListDto()
{
    // TODO: make private?
}

FileListDto::FileListDto(const QString &user, const QString &directory,
                         const FileInfoList &files)
    : EndpointDto(), mUser(user), mDirectory(directory), mFiles(files)
{
    qDebug() << "FileList!" << user << directory/* << files*/;
}

FileListDto::~FileListDto()
{
}

QByteArray FileListDto::fieldString(const FileListDto::Field field)
{
    const QMetaEnum metaEnum = QMetaEnum::fromType<FileListDto::Field>();
    return metaEnum.valueToKey(int(field));
}

QString FileListDto::name() const
{
    return QStringLiteral("FileList");
}

QString FileListDto::path() const
{
    return EndpointDto::path() + QStringLiteral("/filelist");
}

QString FileListDto::description() const
{
    return QStringLiteral("Returns a list of files in a particular folder in "
                          "the cloud");
}

FileListDto FileListDto::fromJson(const QByteArray &data)
{
    QJsonParseError error;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "Wrong JSON data!" << data;
        return FileListDto();
    }

    const QJsonObject main(doc.object());
    const QJsonArray files(main.value(fieldString(Field::Files)).toArray());

    FileInfoList infos;
    for (const auto &value : files) {
        const QJsonObject obj(value.toObject());
        FileInfo info;
        info.name = obj.value(info.fieldString(FileInfo::Name)).toString();
        const QString created(obj.value(info.fieldString(FileInfo::Created))
                                  .toString());
        info.created = QDateTime::fromString(created, Qt::ISODate);
        const QString modified(obj.value(info.fieldString(FileInfo::Modified))
                                   .toString());
        info.modified = QDateTime::fromString(modified, Qt::ISODate);
        const QString size(obj.value(info.fieldString(FileInfo::Size))
                               .toString());
        info.size = size.toLongLong();
        info.isDirectory = obj.value(info.fieldString(FileInfo::IsDirectory))
                               .toBool();
        infos.append(info);
    }

    return FileListDto(main.value(fieldString(Field::User)).toString(),
                       main.value(fieldString(Field::Directory)).toString(),
                       infos);
}

QJsonDocument FileListDto::toJson() const
{
    // TODO: automatic conversion

    QJsonDocument result;
    // TODO: use Q_ENUM to automatically translate enum name to string
    QJsonObject object({
        { fieldString(Field::User), mUser },
        { fieldString(Field::Directory), mDirectory },
    });

    QJsonArray files;
    for (const auto &info : qAsConst(mFiles)) {
        const QJsonObject file({
            { info.fieldString(FileInfo::Name), info.name },
            { info.fieldString(FileInfo::Created), info.created.toUTC()
                                                      .toString(Qt::ISODate) },
            { info.fieldString(FileInfo::Modified), info.modified.toUTC()
                                                       .toString(Qt::ISODate) },
            { info.fieldString(FileInfo::Size), QString::number(info.size) },
            { info.fieldString(FileInfo::IsDirectory), info.isDirectory },
        });
        files.append(file);
    }
    object.insert(fieldString(Field::Files), files);

    result.setObject(object);
    return result;
}

FileListDto FileListDto::fromCbor(const QByteArray &data)
{
    QCborParserError error;
    const QCborValue dataValue(QCborValue::fromCbor(data, &error));

    if (error.error != QCborError::NoError) {
        qWarning() << "Wrong CBOR data!" << data;
        return FileListDto();
    }

    const QCborMap map(dataValue.toMap());
    const QCborArray files(map.value(Field::Files).toArray());

    FileInfoList infos;
    for (const auto value : files) {
        const QCborMap file(value.toMap());
        FileInfo info;
        info.name = file.value(FileInfo::Name).toString();
        info.created = file.value(FileInfo::Created).toDateTime();
        info.modified = file.value(FileInfo::Modified).toDateTime();
        info.size = file.value(FileInfo::Size).toInteger();
        info.isDirectory = file.value(FileInfo::IsDirectory).toBool();

        infos.append(info);
    }

    return FileListDto(map.value(Field::User).toString(),
                       map.value(Field::Directory).toString(),
                       infos);
}

QCborMap FileListDto::toCbor() const
{
    // TODO: automatic conversion

    QCborMap result;
    result.insert(Field::User, mUser);
    result.insert(Field::Directory, mDirectory);

    QCborArray files;
    for (const auto &info : qAsConst(mFiles)) {
        QCborMap file;
        file.insert(FileInfo::Name, info.name);
        file.insert(FileInfo::Created, QCborValue(info.created));
        file.insert(FileInfo::Modified, QCborValue(info.modified));
        file.insert(FileInfo::Size, info.size);
        file.insert(FileInfo::IsDirectory, info.isDirectory);
        files.append(file);
    }
    result.insert(Field::Files, files);
    return result;
}

QString FileListDto::user() const
{
    return mUser;
}

void FileListDto::setUser(const QString &user)
{
    mUser = user;
}

QString FileListDto::directory() const
{
    return mDirectory;
}

void FileListDto::setDirectory(const QString &directory)
{
    mDirectory = directory;
}

FileInfoList FileListDto::files() const
{
    return mFiles;
}

void FileListDto::setFiles(const QFileInfoList &files)
{
    mFiles = files;
}
