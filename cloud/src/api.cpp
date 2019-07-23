#include "api.h"

#include "utils/tags.h"

// TODO: use api/ dir here
#include "apicore.h"

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
    c->setStash(Tags::cloudAppVersion, CloudAppVersion);
    const QStringList endpoints(ApiCore::allEndpoints());
    c->setStash(Tags::endpoints, endpoints);
}

