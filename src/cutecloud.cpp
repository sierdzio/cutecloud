#include "cutecloud.h"

#include "root.h"

#include <Cutelyst/Plugins/StaticSimple/staticsimple.h>
#include <Cutelyst/Plugins/View/Grantlee/grantleeview.h>

using namespace Cutelyst;

cutecloud::cutecloud(QObject *parent) : Application(parent)
{
}

cutecloud::~cutecloud()
{
}

bool cutecloud::init()
{
    new Root(this);
    new StaticSimple(this);
    auto view = new GrantleeView(this);
    view->setIncludePaths({ pathTo("root"), pathTo("root/static") });
    //view->setWrapper("root.html");
    return true;
}

