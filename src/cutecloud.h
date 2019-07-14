#ifndef CUTECLOUD_H
#define CUTECLOUD_H

#include <Cutelyst/Application>

using namespace Cutelyst;

class cutecloud : public Application
{
    Q_OBJECT
    CUTELYST_APPLICATION(IID "cutecloud")
public:
    Q_INVOKABLE explicit cutecloud(QObject *parent = nullptr);
    ~cutecloud();

    bool init();
};

#endif //CUTECLOUD_H

