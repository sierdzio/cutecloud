#include "root.h"

#include "configs/cloudconfig.h"

#include <QDir>
#include <QFileInfo>

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
    const QStringList directories(dir.entryList(QDir::Dirs));
    const QStringList files(dir.entryList(QDir::Files));

    c->setStash("files", files);
    c->setStash("directories", directories);
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

