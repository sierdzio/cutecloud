#include "wasm.h"

#include <QDir>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QDebug>

using namespace Cutelyst;

Wasm::Wasm(QObject *parent) : Controller(parent)
{
}

Wasm::~Wasm()
{
}

void Wasm::index(Context *c)
{
    const QStringList args(c->request()->arguments());

    if (args.isEmpty())
        serveFile(c, QStringLiteral("client.html"));
    else
        serveFile(c, args.at(0));
}

void Wasm::serveFile(Context *c, const QString &fileName)
{
    QDir dir("root/wasm");
    const QString path(dir.absoluteFilePath(fileName));
    QFileInfo fileInfo(path);
    if (fileInfo.exists()) {
        Response *res = c->res();
        const QDateTime currentDateTime = fileInfo.lastModified();
        if (currentDateTime == c->req()->headers().ifModifiedSinceDateTime()) {
            res->setStatus(Response::NotModified);
            qDebug() << "Not modified!";
            return;
        }

        QFile *file = new QFile(path);
        if (file->open(QFile::ReadOnly)) {
            qDebug() << "Serving" << path;
            Headers &headers = res->headers();

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

    qWarning() << "Could not serve" << path;
}

