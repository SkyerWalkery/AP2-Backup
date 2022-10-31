#ifndef AP_PROJ_GRASS_H
#define AP_PROJ_GRASS_H

#include "Area.h"

class Grass: public Area{

    static constexpr const char* TEXTURE = ":/images/grass.png";

public:
    explicit Grass(QGraphicsItem *parent = nullptr);

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 1 };
    int type() const override;

};

#endif //AP_PROJ_GRASS_H
