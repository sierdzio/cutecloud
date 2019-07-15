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
        QStandardPaths::HomeLocation) + "/" + QString(AppName).toLower();
};

#endif // CLOUDCONFIG_H
