#ifndef WASM_H
#define WASM_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class Wasm : public Controller
{
    Q_OBJECT
public:
    explicit Wasm(QObject *parent = nullptr);
    ~Wasm();

    C_ATTR(index, :Path :AutoArgs)
    void index(Context *c);
};

#endif //WASM_H

