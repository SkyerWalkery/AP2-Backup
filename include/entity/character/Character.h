#ifndef AP_PROJ_CHARACTER_H
#define AP_PROJ_CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "Entity.h"


/*
 * Abstract base class of all characters
 * When inherit this, you need to pay attention to these:
 * 1. SunCost needs to be defined, even if cost of your character is 0 too.
 * 2. You may need to override tryAttack() when needed
 */
class Character: public Entity{

protected:

    // Must be set before construct
    // setCharacterSize() should be called
    static qreal CharacterSize;

public:

    static constexpr const int ON_GRASS = 0b01;
    static constexpr const int ON_ROAD = 0b10;

    /* static attribute of a character, needing to be redefined when in subclass
     * if AreaCond & ON_GRASS:
     * then: this character can be placed on grass
     * if AreaCond & ON_ROAD:
     * then: this character can be placed on road
     * A character may be placed on grass and roads both
     */
    static constexpr const int AreaCond = 0b00;

    static constexpr const int SunCost = 0; // Cost to put this character

    using Entity::Entity;

    /*
     * Returns true if character can be placed on area with `cond`
     */
    virtual bool testAreaCond(int cond) = 0;

    static void setCharacterSize(qreal size);

    void attack(Entity* target) override;

};


#endif //AP_PROJ_CHARACTER_H
