#include "apicore.h"

#include "filelist.h"

#include <QDebug>

#define TYPE_NAME(Type) #Type

const QStringList ApiCore::mEndpoints = {
    TYPE_NAME(FileList)
};

QStringList ApiCore::endpoints()
{
    return mEndpoints;
}
