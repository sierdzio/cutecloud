#include "files.h"

#include "configs/cloudconfig.h"
#include "utils/tags.h"

#include <QDir>
#include <QFileInfo>

#include <QMimeDatabase>
#include <QMimeType>

#include <QDebug>

#include <Cutelyst/Upload>

using namespace Cutelyst;

Files::Files(QObject *parent) : Controller(parent)
{
}

Files::~Files()
{
}

void Files::index(Context *c)
{
    qDebug() << "THIS IS FILES";

    // Check if path denotes a known file in cloud storage
    const QString dirtyPath(c->request()->arguments().join(sep));
    // Trim trailing slashes
    const QString path(trimTrailingSlashes(dirtyPath));

    const CloudConfig config;
    const QDir dir(config.storagePath);

    const QString filePathDirty(dir.absolutePath() + sep + path);

    const QFileInfo fileInfo(filePathDirty);
    const QString filePath(fileInfo.canonicalFilePath());

    qDebug() << "Path is:" << path << "file path:" << filePath
             << "exists:" << fileInfo.exists();

    if (fileInfo.exists()) {
        if (fileInfo.isDir()) {
            const QDir dir(filePath);
            const QStringList files(dir.entryList(
                QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot,
                QDir::SortFlag::DirsFirst));
            qDebug() << "LANUCHING TEMPLATE" << path << files;

            c->setStash(Tags::path, path);
            c->setStash(Tags::files, files);
            return;
        }

        // Path exists, allowing download
        Response *res = c->res();
        QFile *file = new QFile(filePath);
        if (file->open(QFile::ReadOnly)) {
            qDebug() << "Serving" << path;
            Headers &headers = res->headers();
            const QDateTime currentDateTime = fileInfo.lastModified();
            if (currentDateTime == c->req()->headers().ifModifiedSinceDateTime()) {
                res->setStatus(Response::NotModified);
                return;
            }

            // set our open file
            res->setBody(file);

            static QMimeDatabase db;
            // use the extension to match to be faster
            QMimeType mimeType = db.mimeTypeForFile(path, QMimeDatabase::MatchExtension);
            if (mimeType.isValid()) {
                headers.setContentType(mimeType.name());
            }

            headers.setContentLength(file->size());

            headers.setLastModified(currentDateTime);
            // Tell Firefox & friends its OK to cache, even over SSL
            headers.setHeader(QStringLiteral("CACHE_CONTROL"), QStringLiteral("public"));

            return;
        }

        qWarning() << "Could not serve" << path << file->errorString();
        return;
    }
}

void Files::upload(Context *c)
{
    qDebug() << "UPLOAD!";

    if (c->request()->isPost()) {
        const auto fileInfo = c->request()->upload("fileToUpload");
        const auto fileData = c->request()->upload("submit");

        if (fileInfo and fileData) {
            const CloudConfig config;
            const QDir dir(config.storagePath);

            // Determine exact save dir:
            const QString relative(c->request()->arguments().join(sep));

            const QString filePath(dir.absolutePath() + sep
                                   + relative + sep
                                   + fileInfo->filename());

            qDebug() << "Saving to:" << filePath
                     << fileInfo->size()
                     << fileInfo->save(filePath);

            index(c);
            return;
        }
    } else {
        // This request is to display contents of "upload" file or directory,
        // not upload action
        index(c);
        return;
    }
}

QString Files::trimTrailingSlashes(const QString &path) const
{
    QString result(path);
    forever {
        if (result == sep or result.isEmpty()) {
            return result;
        }

        const QChar last(result.at(result.size() - 1));
        if (last == '/') {
            result.chop(1);
        } else {
            break;
        }
    }

    return result;
}
