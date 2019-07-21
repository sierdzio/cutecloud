#ifndef TAGS_H
#define TAGS_H

#include <QByteArray>

namespace Tags {
// Config
const QByteArray cloudConfig("core");

// Stash
const QByteArray cloudAppName("CloudAppName");
const QByteArray cloudAppVersion("CloudAppVersion");
const QByteArray storagePath("StoragePath");


const QByteArray title("title");
const QByteArray files("files");
const QByteArray directories("directories");
const QByteArray path("path");
const QByteArray up("..");
const QByteArray endpoints("endpoints");

}

#endif // TAGS_H
