#include "root.h"

#include "configs/cloudconfig.h"
#include "utils/tags.h"

#include <QDir>
#include <QFileInfo>

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
    //qDebug() << "THIS IS INDEX";

    const CloudConfig config;
    c->setStash(Tags::appName, AppName);
    c->setStash(Tags::storagePath, config.storagePath);

    const QDir dir(config.storagePath);
    const QStringList directories(dir.entryList(
        QDir::Dirs | QDir::NoDotAndDotDot));
    const QStringList files(dir.entryList(QDir::Files));

    c->setStash(Tags::files, files);
    c->setStash(Tags::directories, directories);
}

void Root::defaultPage(Context *c)
{
    // Display HTTP 404 page
    c->response()->body() = "404: Page not found!";
    c->response()->setStatus(404);
}

