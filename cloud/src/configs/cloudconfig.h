#ifndef CLOUDCONFIG_H
#define CLOUDCONFIG_H

#include <QStandardPaths>

#include "mconfig.h"

class CloudConfig : public MConfig
{
public:
    CloudConfig();
    ~CloudConfig();

    QString storagePath = QStandardPaths::writableLocation(
        QStandardPaths::HomeLocation) + "/" + QString(CloudAppName).toLower();

    QString appName = CloudAppName;

    //! Simple dirtiness switch. TODO: refactor and make it more proper
    bool dirty = false;
};

#endif // CLOUDCONFIG_H
