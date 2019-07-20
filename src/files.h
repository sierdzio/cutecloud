#ifndef FILES_H
#define FILES_H

#include <Cutelyst/Controller>

using namespace Cutelyst;

class Files : public Controller
{
    Q_OBJECT

public:
    explicit Files(QObject *parent = nullptr);
    ~Files();

    C_ATTR(index, :Path :Args)
    void index(Context *c);

private:
    QString trimTrailingSlashes(const QString &path) const;
};

#endif //FILES_H

