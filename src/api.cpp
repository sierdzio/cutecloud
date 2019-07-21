#include "api.h"

#include "utils/tags.h"

using namespace Cutelyst;

Api::Api(QObject *parent) : Controller(parent)
{
}

Api::~Api()
{
}

void Api::index(Context *c)
{
    c->setStash(Tags::title, tr("API"));
    c->setStash(Tags::appVersion, AppVersion);
    const QStringList endpoints = {
        "fileList"
    };
    c->setStash(Tags::endpoints, endpoints);
}

