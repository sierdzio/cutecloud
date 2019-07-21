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
    //const QStringList arguments(c->request()->arguments());
    //const QString path(arguments.isEmpty()? QString() : arguments.at(0));
    qDebug() << "THIS IS FILES" /*<< arguments << c->request()->path()*/;

    // Check if path denotes a known file in cloud storage
    const QString fullPath(c->req()->path());
    const QString methodName("files/");
    const QString dirtyPath(fullPath.mid(fullPath.indexOf(methodName)
                                         + methodName.size()));
    // Trim trailing slashes
    const QString path(trimTrailingSlashes(dirtyPath));

    const CloudConfig config;
    const QDir dir(config.storagePath);

    const QString filePathDirty(dir.absolutePath() + QStringLiteral("/")
                                + path);

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
    qDebug() << "UPLOAD!" << c->request()->path()
             << c->request()->arguments()
             << c->request()->isPost();
    qDebug() << "datas:" << c->request()->uploads();

    if (c->request()->isPost()) {
        const auto fileInfo = c->request()->upload("fileToUpload");
        const auto fileData = c->request()->upload("submit");

        if (fileInfo and fileData) {
            const CloudConfig config;
            const QDir dir(config.storagePath);

            // Determine exact save dir:
            const QString url(c->request()->path());
            const QString prefix(QStringLiteral("/files/upload/"));
            const QString relative(url.mid(prefix.length() - 1));

            const QString filePath(dir.absolutePath() + QStringLiteral("/")
                                   + relative + QStringLiteral("/")
                                   + fileInfo->filename());

            qDebug() << "Saving to:" << filePath
                     << fileInfo->size()
                     << fileInfo->save(filePath);

            c->forward("index");
        }
    } else {
        // This request is to display contents of "upload" file or directory,
        // not upload action
        c->forward("index");
    }
}

QString Files::trimTrailingSlashes(const QString &path) const
{
    QString result(path);
    forever {
        if (result == QStringLiteral("/") or result.isEmpty()) {
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
