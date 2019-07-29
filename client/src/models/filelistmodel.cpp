#include "filelistmodel.h"

#include <QMetaEnum>

FileListModel::FileListModel(QObject *parent) : QAbstractItemModel(parent)
{
}

FileInfo FileListModel::fileInfo(const int row) const
{
    if (row < 0 or row >= mDto.files().size())
        return FileInfo();

    return mDto.files().at(row);
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
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    if (row <= mDto.files().size())
        return createIndex(row, column, nullptr);
    return QModelIndex();
}

QModelIndex FileListModel::parent(const QModelIndex &child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int FileListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mDto.files().size();
}

int FileListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return QMetaEnum::fromType<FileInfo::Field>().keyCount();
}

bool FileListModel::hasChildren(const QModelIndex &parent) const
{
    if (parent == QModelIndex())
        return true;
    return false;
}

QVariant FileListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();

    if (row >= mDto.files().size())
        return QVariant();

    const FileInfo::Field column = FileInfo::Field(index.column());
    const FileInfo &info = mDto.files().at(row);

    switch (role) {
    case Qt::DisplayRole:
    {
        switch (column) {
        case FileInfo::Name: return info.name;
        case FileInfo::Created: return info.created;
        case FileInfo::Modified: return info.modified;
        case FileInfo::Size: return info.size;
        case FileInfo::IsDirectory: return (info.isDirectory? tr("Dir")
                                     : tr("File"));
        }
    }
    break;
    }

    return QVariant();
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

    return QVariant();
}
