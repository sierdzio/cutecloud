#include "cutecloud.h"

#include "root.h"
#include "settings.h"
#include "files.h"
#include "api.h"
#include "wasm.h"

#include <Cutelyst/Plugins/StaticSimple/staticsimple.h>
#include <Cutelyst/Plugins/View/Grantlee/grantleeview.h>
#include <QCoreApplication>

using namespace Cutelyst;

cutecloud::cutecloud(QObject *parent) : Application(parent)
{
    auto app = QCoreApplication::instance();
    app->setApplicationName(CloudAppName);
    app->setOrganizationName(CompanyName);
    app->setOrganizationDomain(CompanyDomain);
    app->setApplicationVersion(CloudAppVersion);
}

cutecloud::~cutecloud()
{
}

bool cutecloud::init()
{
    new Root(this);
    new Settings(this);
    new Files(this);
    new Api(this);
    new Wasm(this);

    new StaticSimple(this);
    auto view = new GrantleeView(this);
    view->setIncludePaths({ pathTo("root")/*, pathTo("root/static")*/ });
    view->setWrapper("wrapper.html");

    return true;
}

