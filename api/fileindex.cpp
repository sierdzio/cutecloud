#include "fileindex.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>

//FileIndex::FileIndex(const QString &path) : mPath(path), mHash(index(path))
//{
//}

//QString FileIndex::path() const
//{
//    return mPath;
//}

//QByteArray FileIndex::hash() const
//{
//    return mHash;
//}

QByteArray FileIndex::index(const QString &path, const QString &workingDir)
{
    // TODO: use the working dir!
    Q_UNUSED(workingDir);

    const QByteArray sep = QByteArrayLiteral(";");
    const QFileInfo info(path);

    if (info.exists()) {
        // TODO: also calculate hash from permissions, symlink, hidden, etc.
        const QByteArray data(
            info.fileName().toUtf8() + sep
            + QByteArray::number(info.size()) + sep
            + info.birthTime().toUTC().toString(Qt::DateFormat::ISODate).toLatin1() + sep
            + info.lastModified().toUTC().toString(Qt::DateFormat::ISODate).toLatin1() + sep
            + info.metadataChangeTime().toUTC().toString(Qt::DateFormat::ISODate).toLatin1() + sep
            );
        return QCryptographicHash::hash(data, QCryptographicHash::RealSha3_512);
    }

    return QByteArray();
}

FileList FileIndex::directoryIndex(const QString &path)
{
    FileList result;

    const int toCut = path.length() + (path.endsWith(QStringLiteral("/"))? 1 : 0);
    QDirIterator it(path, QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        const QString filePath(it.next().mid(toCut));
        result.insert(filePath, index(filePath));

    }

    return result;
}
