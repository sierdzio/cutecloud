#include "filelist.h"

#include <QDebug>

FileList::FileList(QObject *parent) : QObject(parent) {
    qDebug() << "FileList!";
}

FileList::~FileList()
{
}
