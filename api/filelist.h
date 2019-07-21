#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>

class FileList : public QObject
{
    Q_OBJECT

public:
    FileList(QObject *parent = nullptr);
    ~FileList();
};

#endif // FILELIST_H
