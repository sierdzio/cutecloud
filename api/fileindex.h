#ifndef FILEINDEX_H
#define FILEINDEX_H

#include <QByteArray>
#include <QHash>
#include <QString>

class FileIndex;

using FileList = QHash<QString, FileIndex>;

/*!
 * Indexes files in given directory using a lightweight metadata-only hash.
 */
class FileIndex
{
public:
    enum Mode {
        MetaDataIndex = 0x0001,
        FileContentsIndex = 0x0002,
        FullIndex = MetaDataIndex | FileContentsIndex
    };

    /*!
     * Returns lightweight hash for a single file (or directory **descriptor**)
     * found at \a path.
     */
    static FileIndex file(const QString &path,
                          const QString &workingDir = QString(),
                          const Mode indexingMode = MetaDataIndex);

    /*!
     * *Recursively* generates index() for all files and directories in
     * \a path and returns a FileList object. The paths in FileList will
     * not include \a path (in other words, \a path is considered "working
     * directory").
     */
    static FileList directory(const QString &path,
                              const Mode indexingMode = MetaDataIndex);

    static QString toString(const FileList &list);

    QString toString() const;

    QString path() const;
    QByteArray metaDataHash() const;
    QByteArray dataHash() const;

private:
    static QString sep;

    QString mPath;
    QByteArray mMetaDataHash;
    QByteArray mDataHash;
};

#endif // FILEINDEX_H
