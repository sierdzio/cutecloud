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

    C_ATTR(index, :Path :Args)
    void index(Context *c);

private:
    void serveFile(Context *c, const QString &fileName);
};

#endif //WASM_H

