#ifndef TAGS_H
#define TAGS_H

#include <QByteArray>

namespace Tags {
// Config
const QByteArray cloudConfig("core");

// Query params
const QByteArray json("json");
const QByteArray cbor("cbor");

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
const QByteArray endpoint("endpoint");
const QByteArray description("description");
const QByteArray parameters("parameters");
}

#endif // TAGS_H
