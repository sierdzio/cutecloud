#ifndef API_H
#define API_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class Api : public Controller
{
    Q_OBJECT

public:
    explicit Api(QObject *parent = nullptr);
    ~Api();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);

    C_ATTR(filelist, :Path("filelist") :AutoArgs)
    void fileList(Context *c);
};

#endif //API_H

