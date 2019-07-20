#include "settings.h"

using namespace Cutelyst;

Settings::Settings(QObject *parent) : Controller(parent)
{
}

Settings::~Settings()
{
}

void Settings::index(Context *c)
{
    c->response()->body() = "Matched Controller::Settings in Settings.";
}

