#ifndef SETTINGS_H
#define SETTINGS_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class Settings : public Controller
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    ~Settings();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);
};

#endif //SETTINGS_H

