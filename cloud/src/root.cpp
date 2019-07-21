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
    c->setStash(Tags::title, tr("Home"));
    c->setStash(Tags::cloudAppName, CloudAppName);
    c->setStash(Tags::storagePath, config.storagePath);

    const QDir dir(config.storagePath);
    const QStringList files(dir.entryList(
        QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot,
        QDir::SortFlag::DirsFirst));

    c->setStash(Tags::files, files);
}

void Root::defaultPage(Context *c)
{
    // Display HTTP 404 page
    c->response()->body() = "404: Page has not been found!";
    c->response()->setStatus(404);
}

