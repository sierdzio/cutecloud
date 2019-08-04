#ifndef CONFIG_H
#define CONFIG_H

#include "mconfig.h"

class Config : public MConfig
{
public:
    Config();
    ~Config();

    QString storagePath;
    QString serverUrl;
    QString userId; // TODO: support multiple users in single app instance?
    // Store user ID and token instead?

    bool dirty = false;
};

#endif // CONFIG_H
