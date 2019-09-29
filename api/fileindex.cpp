#include "fileindex.h"

#include <QCryptographicHash>
#include <QDirIterator>
#include <QDateTime>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QDir>

QString FileIndex::sep = QStringLiteral("/");

FileIndex FileIndex::file(const QString &path, const QString &workingDir,
                          const Mode indexingMode)
{
    FileIndex result;

    if (workingDir.endsWith(QStringLiteral("/")) == false) {
        qWarning() << "ERROR: working dir does not end with a forward slash";
        return result;
    }

    const QByteArray sep = QByteArrayLiteral(";");
    const QFileInfo info(workingDir + path);

    result.mPath = path;

    if (info.exists() == false) {
        return result;
    }

    if (indexingMode & MetaDataIndex) {
        // TODO: also calculate hash from permissions, symlink, hidden, etc.?
        const QByteArray data(
            info.fileName().toUtf8() + sep
            + QByteArray::number(info.size()) + sep
            + info.birthTime().toUTC().toString(Qt::DateFormat::ISODate).toLatin1() + sep
            + info.lastModified().toUTC().toString(Qt::DateFormat::ISODate).toLatin1() + sep
//            + info.metadataChangeTime().toUTC().toString(Qt::DateFormat::ISODate).toLatin1() + sep
            );

        result.mMetaDataHash = QCryptographicHash::hash(
            data, QCryptographicHash::RealSha3_512);
    }

    if (indexingMode & FileContentsIndex) {
        QFile file(info.filePath());

        if (file.open(QFile::ReadOnly)) {
            QCryptographicHash hash(QCryptographicHash::RealSha3_512);
            hash.addData(&file);
            result.mDataHash = hash.result();
        }
    }

    return result;
}

FileIndexList FileIndex::directory(const QString &path, const Mode indexingMode)
{
    FileIndexList result;

    const QString workingDir(path + (path.endsWith(sep)? QString() : sep));
    const int toCut = workingDir.length();

    QDirIterator it(path, QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files
                        | QDir::Hidden,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
        const QString current(it.next().mid(toCut));
        //qDebug() << "Indexing:" << current;
        FileIndex index = file(current, workingDir, indexingMode);
        result.insert(index.path(), index);
    }

    return result;
}

QString FileIndex::toString(const FileIndexList &list)
{
    QString result;
    for (const auto &index : list) {
        result.append(index.toString() + QStringLiteral("\n"));
    }
    return result;
}

QString FileIndex::toString() const
{
    return QString(mPath + QStringLiteral(": ") + mMetaDataHash.toHex()
                   + QStringLiteral(": ") + mDataHash.toHex());
}

QString FileIndex::path() const
{
    return mPath;
}

QByteArray FileIndex::metaDataHash() const
{
    return mMetaDataHash;
}

QByteArray FileIndex::dataHash() const
{
    return mDataHash;
}
