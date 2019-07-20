#include "cloudconfig.h"

#include "utils/tags.h"

CloudConfig::CloudConfig() : MConfig(Tags::cloudConfig)
{
    CONFIG_VALUE(storagePath, QMetaType::QString);
    CONFIG_VALUE(appName, QMetaType::QString);
    load();
}

CloudConfig::~CloudConfig()
{
    // TODO: save if there is no config file (so that default settings are
    // stored and editable)
    if (dirty)
        save();
}
