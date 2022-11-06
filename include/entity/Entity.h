#ifndef AP_PROJ_ENTITY_H
#define AP_PROJ_ENTITY_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>

/*
 * Abstract base class of all entities
 * Inherited by Character and Monster\
 * Note:
 * 1. You may need to override attack() and attacked() when needed
 */
class Entity: public QGraphicsPixmapItem{

protected:

    int damage_ = 0; // Damage made per attack

    int recharge_time_ = 0; // Time (ms) to recharge before an attack

    int recharged_ = 0; // Time (ms) that the character has recharged since last attack

    qreal attack_range_ = 0; // Attack range (num of AREA_SIZE)

    int health_ = 0;

    static qreal AreaSize; // Must be set before construct

public:

    using QGraphicsPixmapItem::QGraphicsPixmapItem;

    //Below are setters and getters
    int getDamage() const;

    void setDamage(int damage);

    int gerRechargeTime() const;

    void setRechargeTime(int time);

    qreal getAttackRange() const;

    void setAttackRange(qreal range);

    int getHealth() const;

    void setHealth(int health);


    static void setAreaSize(qreal size);

    // Helper methods

    /*
     * Returns if an entity is in attack range
     *
     * @param target entity
     */
    bool inAttackRange(Entity* target) const;

    /*
     * Returns if the entity is ready to make an attack
     * i.e. recharged_ >= recharge_time
     */
    bool readyToAttack() const;

    /*
     * Add to recharged_
     */
    void recharge(int time);

    bool isAlive() const;

    // Virtual methods that default ones are given
    /*
     * Try to attack an entity
     * Note: target->attacked() would be called
     */
    virtual void attack(Entity* monster);

    virtual void attacked(int damage);

};

#endif //AP_PROJ_ENTITY_H
