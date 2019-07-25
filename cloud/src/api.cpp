#include "api.h"

#include "utils/tags.h"

// TODO: use api/ dir here
#include "apicore.h"
#include "filelistdto.h"

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

void Api::filelist(Context *c)
{
    const auto &params = c->request()->queryParams();
    const FileListDto dto;

    qDebug() << "Params:" << params;

    if (params.contains(Tags::json)) {
        c->response()->body() = dto.toJson().toJson();
    } else if (params.contains(Tags::cbor)) {
        qDebug() << "Returning CBOR" << dto.toCbor().toCborValue().toCbor();
        c->response()->body() = dto.toCbor().toCborValue().toCbor();
    } else {
        c->setStash("template", "api/endpoint.html");
        c->setStash(Tags::title, dto.name());
        c->setStash(Tags::endpoint, dto.name());
        c->setStash(Tags::description, dto.description());
        c->setStash(Tags::parameters, "nothing yet...");
    }
}
