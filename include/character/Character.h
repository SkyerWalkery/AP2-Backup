#ifndef AP_PROJ_CHARACTER_H
#define AP_PROJ_CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "Monster.h"


/*
 * Abstract base class of all characters
 * When inherit this, you need to pay attention to these:
 * 1. SunCost needs to be defined, even if cost of your character is 0 too.
 * 2. You may need to override attack() when needed
 * 3. MonsterSize must be set properly before used
 */
class Character: public QGraphicsPixmapItem{

protected:

    int damage_ = 0; // Damage to monster per attack

    int recharge_time_ = 0; // Time (ms) to recharge before an attack

    qreal attack_range_ = 0; // Attack range (num of AREA_SIZE)

    int health_ = 0; // Only for characters that can be put on roads

    static qreal CharacterSize; // Must be set before construct

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

    explicit Character(QGraphicsItem *parent = nullptr);

    //Below are setters and getters
    int getDamage() const;

    void setDamage(int damage);

    int gerRechargeTime() const;

    void setRechargeTime(int time);

    qreal getAttackRange() const;

    void setAttackRange(qreal range);

    int getHealth() const;

    void setHealth(int health);

    /*
     * Returns true if character can be placed on area with `cond`
     */
    virtual bool testAreaCond(int cond) = 0;

    static void setCharacterSize(qreal size);

    // Helper methods

    /*
     * Returns if pos is in character's attack range
     *
     * @param scene pos of target
     */
    bool inAttackRange(const QPointF& pos) const;

    // Virtual methods that default ones are given
    /*
     * Try to attack a monster
     * Note: monster->attacked() would be called
     */
    virtual void attack(Monster* monster);

};


#endif //AP_PROJ_CHARACTER_H
