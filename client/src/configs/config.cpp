#include "config.h"

#include "utils/tags.h"

Config::Config() : MConfig(Tags::clientConfig)
{
    CONFIG_VALUE(storagePath, QMetaType::QString);
    CONFIG_VALUE(serverUrl, QMetaType::QString);
    CONFIG_VALUE(userId, QMetaType::QString);

    load();
}

Config::~Config()
{
    if (dirty)
        save();
}
