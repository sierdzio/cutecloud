#include "api.h"

#include "utils/tags.h"
#include "configs/cloudconfig.h"

// TODO: use api/ dir here
#include "apicore.h"
#include "filelistdto.h"

#include <QDir>
#include <QFileInfo>

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
    const QString &user("default");
    // We skip first arg because it is endpoint name
    const auto dirPath(c->request()->arguments().mid(1).join(sep));
    const CloudConfig config;
    const QDir dir(config.storagePath + sep + dirPath);
    const QFileInfoList files(dir.entryInfoList(QDir::Dirs | QDir::Files
                                                    | QDir::NoDotAndDotDot,
                                                QDir::SortFlag::DirsFirst));

    const FileListDto dto(user, dirPath, files);

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