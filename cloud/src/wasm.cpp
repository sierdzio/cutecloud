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
    c->response()->body() = "Matched Controller::Wasm in Wasm.";
}

