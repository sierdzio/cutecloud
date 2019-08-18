#ifndef FILEINDEX_H
#define FILEINDEX_H

#include <QByteArray>
#include <QHash>
#include <QString>

using FileList = QHash<QString, QByteArray>;

/*!
 * Indexes files in given directory using a lightweight metadata-only hash.
 */
class FileIndex
{
public:
    /*!
     * Returns lightweight hash for a single file (or directory **descriptor**)
     * found at \a path.
     */
    static QByteArray index(const QString &path,
                            const QString &workingDir = QString());

    /*!
     * *Recursively* generates index() for all files and directories in
     * \a path and returns a FileList object. The paths in FileList will
     * not include \a path (in other words, \a path is considered "working
     * directory").
     */
    static FileList directoryIndex(const QString &path);
};

#endif // FILEINDEX_H
