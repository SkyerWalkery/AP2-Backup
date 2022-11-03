#ifndef AP_PROJ_BOAR_H
#define AP_PROJ_BOAR_H

#include "Monster.h"

class Boar: public Monster{

    static constexpr const char* TEXTURE = ":/images/boar.png";

public:

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 101 };
    int type() const override;

    explicit Boar(QGraphicsItem *parent = nullptr);
};

#endif //AP_PROJ_BOAR_H
