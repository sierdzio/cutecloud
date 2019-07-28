#pragma once

#include "endpointdto.h"

#include <QVector>
#include <QFileInfoList>

class FileInfo {
public:
    enum Field {
        Name,
        Created,
        Modified,
        Size,
        IsDirectory
    };

    FileInfo(const QFileInfo &info);

    QString name;
    QDateTime created;
    QDateTime modified;
    qint64 size;
    bool isDirectory;
};

using FileInfoList = QVector<FileInfo>;

class FileListDto : public EndpointDto
{
public:
    // TODO: automatic field registration! (use Q_ENUM, too)
    enum Fields {
        User,
        Directory,
        Files
    };    

    FileListDto(const QString &user, const QString &directory,
                const QFileInfoList &files);
    virtual ~FileListDto();

    QString name() const final;
    QString description() const final;

    static auto fromJson(const QByteArray &data);
    QJsonDocument toJson() const final;

    static auto fromCbor(const QByteArray &data);
    QCborMap toCbor() const final;

    QString user() const;
    void setUser(const QString &user);

    QString directory() const;
    void setDirectory(const QString &directory);

    QFileInfoList files() const;
    void setFiles(const QFileInfoList &files);

private:
    QString mUser;
    QString mDirectory;
    QFileInfoList mFiles;
};
