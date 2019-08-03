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
    c->setStash(Tags::cloudAppName, config.appName);
    c->setStash(Tags::cloudAppVersion, CloudAppVersion);
    c->setStash(Tags::storagePath, config.storagePath);
    /*
     * TODO:
     * * storage encryption
     * * allow HTTP (unencrypted) - perhaps it should be disabled in release
     *   builds with **NO** option to enable
     * * theming
     * * user settings
     * * user management
     * * etc.
     */

}

