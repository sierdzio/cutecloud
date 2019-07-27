#pragma once

#include "endpointdto.h"

#include <QVector>
#include <QFileInfoList>

//class FileInfo {

//};

//using FileInfoList = QVector<FileInfo>;

class FileListDto : public EndpointDto
{
public:
    // TODO: automatic field registration!
    enum Fields {
        User,
        Directory,
        Files
    };

    enum FileInfo {
        Name,
        Created,
        Modified,
        Size,
        IsDirectory
    };

    FileListDto(const QString &user, const QString &directory,
                const QFileInfoList &files);
    virtual ~FileListDto();

    QString name() const final;
    QString description() const final;

    QJsonDocument toJson() const final;
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
