#include "cloudconfig.h"

#include "utils/tags.h"

CloudConfig::CloudConfig() : MConfig(Tags::cloudConfig)
{
    CONFIG_VALUE(storagePath, QMetaType::QString);
    load();
}

CloudConfig::~CloudConfig()
{
    save();
}
