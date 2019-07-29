#ifndef FILELISTMODEL_H
#define FILELISTMODEL_H

#include <QObject>
#include <QAbstractItemModel>

#include "filelistdto.h"

class FileListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit FileListModel(QObject *parent = nullptr);

    FileListDto fileList() const;
    void setFileList(const FileListDto &dto);

    QModelIndex index(int row, int column, const QModelIndex &parent) const final;
    QModelIndex parent(const QModelIndex &child) const final;
    int rowCount(const QModelIndex &parent) const final;
    int columnCount(const QModelIndex &parent) const final;
    QVariant data(const QModelIndex &index, int role) const final;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const final;

private:
    const QString mFormat = QStringLiteral("yyyy-MM-dd HH:mm");

    FileListDto mDto;
};

#endif // FILELISTMODEL_H
