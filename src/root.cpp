#include "root.h"

using namespace Cutelyst;

Root::Root(QObject *parent) : Controller(parent)
{
}

Root::~Root()
{
}

void Root::index(Context *c)
{
    c->response()->body() = "Welcome to " AppName ", v" AppVersion "<br/>"
                            "Cloud storage is located in: "
        + mConfig.storagePath.toLatin1();
}

void Root::defaultPage(Context *c)
{
    c->response()->body() = "Page not found!";
    c->response()->setStatus(404);
}

