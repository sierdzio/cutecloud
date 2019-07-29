#include "filelistmodel.h"

FileListModel::FileListModel(QObject *parent) : QAbstractItemModel(parent)
{
}

FileListDto FileListModel::fileList() const
{
    return mDto;
}

void FileListModel::setFileList(const FileListDto &dto)
{
    beginResetModel();
    mDto = dto;
    endResetModel();
}

QModelIndex FileListModel::index(int row, int column, const QModelIndex &parent) const
{

}

QModelIndex FileListModel::parent(const QModelIndex &child) const
{

}

int FileListModel::rowCount(const QModelIndex &parent) const
{

}

int FileListModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
//            (file.isDirectory ? QStringLiteral("Dir") : QStringLiteral("File"))
}

QVariant FileListModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{
    Q_UNUSED(orientation);

    if (section < 0 or section >= columnCount(QModelIndex())
        or role != Qt::DisplayRole) {
        return QVariant();
    }

    const FileInfo::Field column = FileInfo::Field(section);

    switch (column) {
    case FileInfo::Name: return tr("Name");
    case FileInfo::Created: return tr("Created");
    case FileInfo::Modified: return tr("Modified");
    case FileInfo::Size: return tr("Size");
    case FileInfo::IsDirectory: return tr("Type");
    }

}
