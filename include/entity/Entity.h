#ifndef AP_PROJ_ENTITY_H
#define AP_PROJ_ENTITY_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QList>
#include <QHash>
#include "BuffUtil.h"
#include "Element.h"
#include "ActionAttack.h"

/**
 * Abstract base class of all entities
 * Inherited by Character and Monster
 * Note:
 * * You may need to override attack() and attacked() when needed;
 * * damage_, recharge_time and attack_range_ should be set if you want to make a valid tryAttack
 * * If one entity cannot be attacked, can_be_attacked_ should be set false
 */
class Entity: public QGraphicsPixmapItem{

protected:

    // Texture of the entity
    // Note: You should provide an image with orientation towards right by default
    // See why in flipHorizontally() and its usage
    QPixmap texture_pixmap_;
    bool is_horizontally_flipped_ = false;

    int damage_ = 0; // Damage made per tryAttack

    int recharge_time_ = 0; // Time (ms) to recharge before an tryAttack

    int recharged_ = 0; // Time (ms) that the character has recharged since last tryAttack

    qreal attack_range_ = 0; // Attack range (num of AREA_SIZE)

    int health_ = 1;
    int max_health_ = 1;

    bool can_be_attacked_ = true; // Some entities, such as ELf (on grass), cannot be attacked

    // buffs of this entity
    // key is Buff type, which is enum (refer to Buff.h)
    // value is duration left now (ms)
    QHash<Buff, int> buffs_;

    // Refer to the design in Genshin Impact
    // Element aura is created through an elemental attack
    // For simplicity, only one aura is allowed
    Element element_aura_ = Element::NONE;

    static qreal AreaSize; // Must be set before construct

    static int GameRefreshInterval; // Must be set before construct

    static qreal distanceBetween(const QPointF &p1, const QPointF &p2);

    /**
     * Flip the texture of entity.
     * e.g. when a monster try to change its moving direction
     */
    void flipHorizontally();

public:

    explicit Entity(QGraphicsItem *parent = nullptr);

    //Below are setters and getters
    int getDamage() const;

    void setDamage(int damage);

    int gerRechargeTime() const;

    void setRechargeTime(int time);

    qreal getAttackRange() const;

    void setAttackRange(qreal range);

    int getHealth() const;

    void setHealth(int health);

    int getMaxHealth() const;

    bool canBeAttacked() const;


    static void setAreaSize(qreal size);

    static void setRefreshInterval(int interval);

    // Helper methods
    /**
     * Returns if an entity is in tryAttack range
     *
     * @param  target target entity
     */
    bool inAttackRange(Entity* target) const;

    /**
     * Returns if the entity is ready to make an tryAttack
     * i.e. recharged_ >= recharge_time
     */
    bool readyToAttack() const;

    /**
     * Add refresh interval to recharged_
     */
    void recharge();

    bool isAlive() const;

    // Virtual methods that default ones are given
    /**
     * Try to attack one or more entities
     * Default implementation is to tryAttack the nearest one
     * Note: target->attacked() would be called
     */
    virtual void tryAttack(const QList<Entity*>& targets);

    // You can override this method to add effect when attacking an entity
    virtual void attack(ActionAttack& action);

    virtual void attacked(ActionAttack& action);

    /**
     * Update buffs on the entity, called once every frame (timer's interval)
     * 1. subtract time (time since last call) from each buff's duration left
     * 2. if dur <= 0, remove it from buffs_
     * 3. do things of buff letting you do, e.g. lose health if corroded
     *
     * @param time: time since last call, i.e. main timer's interval in GameField
     */
    virtual void manageBuff();

    /**
     * Add buff to the entity, whose duration is `duration`
     * If buff exists, add `duration` to buffs_[buff]
     */
    virtual void addBuff(Buff buff, int duration);

    /**
     * Returns if the entity has specific buff
     */
     bool hasBuff(Buff buff) const;

};

#endif //AP_PROJ_ENTITY_H
