#ifndef AP_PROJ_GRASS_H
#define AP_PROJ_GRASS_H

#include "Area.h"

class Grass: public Area{

    static constexpr const char* TEXTURE = ":/images/grass.png";

    // If this area has a character or other objects
    bool occupied_ = false;

public:
    explicit Grass(QGraphicsItem *parent = nullptr);

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 1 };
    int type() const override;

    bool isOccupied() const;

    void setOccupied(bool occupied);
};

#endif //AP_PROJ_GRASS_H
