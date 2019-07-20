#include "cutecloud.h"

#include "root.h"
#include "settings.h"
#include "files.h"

//#include <Cutelyst/Plugins/StaticSimple/staticsimple.h>
#include <Cutelyst/Plugins/View/Grantlee/grantleeview.h>
#include <QCoreApplication>

using namespace Cutelyst;

cutecloud::cutecloud(QObject *parent) : Application(parent)
{
    auto app = QCoreApplication::instance();
    app->setApplicationName(AppName);
    app->setOrganizationName(CompanyName);
    app->setOrganizationDomain(CompanyDomain);
    app->setApplicationVersion(AppVersion);
}

cutecloud::~cutecloud()
{
}

bool cutecloud::init()
{
    new Root(this);
    new Settings(this);
    new Files(this);

    //new StaticSimple(this);
    auto view = new GrantleeView(this);
    view->setIncludePaths({ pathTo("root"), pathTo("root/static") });
    //view->setWrapper("root.html");
    return true;
}

