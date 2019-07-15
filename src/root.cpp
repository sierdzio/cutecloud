#include "root.h"

#include "configs/cloudconfig.h"

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::index(Context *c)
{
    CloudConfig config;
    //c->response()->body() = "Welcome to " AppName ", v" AppVersion "<br/>"
    //                        "Cloud storage is located in: "
    //    + config.storagePath.toLatin1();

    c->setStash("AppName", AppName);
    c->setStash("AppVersion", AppVersion);
    c->setStash("StoragePath", config.storagePath);
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

