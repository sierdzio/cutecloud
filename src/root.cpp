#include "root.h"

#include "configs/cloudconfig.h"

#include <QDir>
#include <QFileInfo>

#include <QMimeDatabase>
#include <QMimeType>

#include <QDebug>

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::index(Context *c)
{
    const CloudConfig config;
    c->setStash("AppName", AppName);
    c->setStash("AppVersion", AppVersion);
    c->setStash("StoragePath", config.storagePath);

    const QDir dir(config.storagePath);
    const QStringList directories(dir.entryList(
        QDir::Dirs | QDir::NoDotAndDotDot));
    const QStringList files(dir.entryList(QDir::Files));

    c->setStash("files", files);
    c->setStash("directories", directories);
}

void Root::defaultPage(Context *c)
{
    // Check if path denotes a known file in cloud storage
    const QString path(c->req()->path());

    const CloudConfig config;
    const QDir dir(config.storagePath);

    const QString filePath(dir.absolutePath() + QStringLiteral("/")
                           + path);

    const QFileInfo fileInfo(filePath);

    qDebug() << "Path is:" << path << "file path:" << filePath
             << "exists:" << fileInfo.exists();

    if (fileInfo.exists()) {
        if (fileInfo.isDir()) {
            index(c);
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

    // Display HTTP 404 page
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

