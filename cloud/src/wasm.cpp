#include "wasm.h"

using namespace Cutelyst;

Wasm::Wasm(QObject *parent) : Controller(parent)
{
}

Wasm::~Wasm()
{
}

void Wasm::index(Context *c)
{
    // TODO: remove SimpleStatic, use this controller to serve the WASM files!

    //c->response()->body() = "Matched Controller::Wasm in Wasm.";
    c->setStash("template", "wasm/client.html");
}

