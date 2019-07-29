#pragma once

#include "endpointdto.h"

#include <QVector>
#include <QFileInfoList>

class FileInfo
{
    Q_GADGET

public:
    enum Field {
        Name,
        Created,
        Modified,
        Size,
        IsDirectory
    }; Q_ENUM(Field)

    FileInfo();
    FileInfo(const QFileInfo &info);
    static QByteArray fieldString(const FileInfo::Field field);

    QString name;
    QDateTime created;
    QDateTime modified;
    qint64 size;
    bool isDirectory;
};

class FileInfoList : public QVector<FileInfo>
{
public:
    FileInfoList(const QFileInfoList &list);

    using QVector<FileInfo>::QVector;
    using QVector<FileInfo>::append;

    // TODO: qDebug() << operator
};

class FileListDto : public EndpointDto
{
    Q_GADGET

public:
    // TODO: automatic field registration! (use Q_ENUM, too)
    enum Field {
        User,
        Directory,
        Files
    }; Q_ENUM(Field)

    FileListDto();
    FileListDto(const QString &user, const QString &directory,
                const FileInfoList &files);
    virtual ~FileListDto();

    static QByteArray fieldString(const FileListDto::Field field);

    QString name() const final;
    QString path() const final;
    QString description() const final;

    static FileListDto fromJson(const QByteArray &data);
    QJsonDocument toJson() const final;

    static FileListDto fromCbor(const QByteArray &data);
    QCborMap toCbor() const final;

    QString user() const;
    void setUser(const QString &user);

    QString directory() const;
    void setDirectory(const QString &directory);

    FileInfoList files() const;
    void setFiles(const QFileInfoList &files);

private:
    QString mUser;
    QString mDirectory;
    FileInfoList mFiles;
};
