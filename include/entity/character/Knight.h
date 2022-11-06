#ifndef AP_PROJ_KNIGHT_H
#define AP_PROJ_KNIGHT_H

#include "Character.h"


class Knight: public Character{

public:

    static constexpr const char* TEXTURE = ":/images/knight.png";

    static constexpr const int AreaCond = Character::ON_GRASS | Character::ON_ROAD;

    static constexpr const int SunCost = 0; // Cost to put this character

    explicit Knight(QGraphicsItem *parent = nullptr);

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 202 };
    int type() const override;

    bool testAreaCond(int cond) override;

};


#endif //AP_PROJ_KNIGHT_H
