#include "filelistdto.h"
#include "apicore.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QCborArray>
#include <QCborValue>

#include <QDebug>

FileListDto::FileListDto(const QString &user, const QString &directory,
                         const QFileInfoList &files)
    : EndpointDto(), mUser(user), mDirectory(directory), mFiles(files)
{
    qDebug() << "FileList!" << user << directory << files;
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

auto FileListDto::fromJson(const QByteArray &data)
{
    QJsonParseError error;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &error);
    const QJsonObject main(doc.object());
    const QJsonArray files(main.value("files").toArray());

    QFileInfoList infos;
//    for (const auto &value : files) {
//        infos.append(QFileInfo())
//    }

    return FileListDto(main.value("user").toString(),
                       main.value("directory").toString(),
                       infos);
}

QJsonDocument FileListDto::toJson() const
{
    // TODO: automatic conversion

    QJsonDocument result;
    // TODO: use Q_ENUM to automatically translate enum name to string
    QJsonObject object({
        { "user", mUser },
        { "directory", mDirectory },
    });

    QJsonArray files;
    for (const auto &info : qAsConst(mFiles)) {
        const QJsonObject file({
            { "name", info.fileName() },
            { "created", info.birthTime().toSecsSinceEpoch() },
            { "modified", info.lastModified().toSecsSinceEpoch() },
            { "size", info.size() },
            { "isDirectory", info.isDir() },
        });
        files.append(file);
    }
    object.insert("files", files);

    result.setObject(object);
    return result;
}

auto FileListDto::fromCbor(const QByteArray &data)
{

}

QCborMap FileListDto::toCbor() const
{
    // TODO: automatic conversion

    QCborMap result;
    result.insert(Fields::User, mUser);
    result.insert(Fields::Directory, mDirectory);

    QCborArray files;
    for (const auto &info : qAsConst(mFiles)) {
        QCborMap file;
        file.insert(FileInfo::Name, info.fileName());
        file.insert(FileInfo::Created, info.birthTime().toSecsSinceEpoch());
        file.insert(FileInfo::Modified, info.lastModified().toSecsSinceEpoch());
        file.insert(FileInfo::Size, info.size());
        file.insert(FileInfo::IsDirectory, info.isDir());
        files.append(file);
    }
    result.insert(Fields::Files, files);
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

QFileInfoList FileListDto::files() const
{
    return mFiles;
}

void FileListDto::setFiles(const QFileInfoList &files)
{
    mFiles = files;
}

FileInfo::FileInfo(const QFileInfo &info)
{
    name = info.fileName();
    created = info.birthTime();
    modified = info.lastModified();
    size = info.size();
    isDirectory = info.isDir();
}
