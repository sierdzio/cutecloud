#include "cutecloud.h"

#include "root.h"

using namespace Cutelyst;

cutecloud::cutecloud(QObject *parent) : Application(parent)
{
}

cutecloud::~cutecloud()
{
}

bool cutecloud::init()
{
    new Root(this);

    return true;
}

