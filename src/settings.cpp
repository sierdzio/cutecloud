#include "settings.h"

#include "utils/tags.h"
#include "configs/cloudconfig.h"

using namespace Cutelyst;

Settings::Settings(QObject *parent) : Controller(parent)
{
}

Settings::~Settings()
{
}

void Settings::index(Context *c)
{
    // Not const because it can be modified in Settings
    /*const*/ CloudConfig config;
    //config.dirty = true;
    c->setStash(Tags::title, tr("Settings"));
    c->setStash(Tags::appName, config.appName);
    c->setStash(Tags::appVersion, AppVersion);
    c->setStash(Tags::storagePath, config.storagePath);
}

