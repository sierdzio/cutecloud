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

    C_ATTR(filelist, :Path :Args)
    void filelist(Context *c);

    C_ATTR(filelist, :Path :Args)
    void fileindex(Context *c);

private:
    const QLatin1String sep = QLatin1String("/");
};

#endif //API_H

