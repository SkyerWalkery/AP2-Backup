#ifndef AP_PROJ_CHARACTER_H
#define AP_PROJ_CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


/*
 * Abstract base class of all characters
 * When inherit this, you need to pay attention to these:
 * 1. SunCost needs to be defined, even if cost of your character is 0 too.
 * 2. You may need to override attack() when needed
 */
class Character: public QGraphicsPixmapItem{

    int damage_ = 0; // Damage to monster per attack

    int recharge_time_ = 0; // Time (ms) to recharge before an attack

    qreal attack_range_ = 0; // Attack range (px)

    int health_ = 0; // Only for characters that can be put on roads

public:

    static constexpr const int SunCost = 0; // Cost to put this character

    Character(QGraphicsItem *parent = nullptr);

    //Below are setters and getters
    int getDamage() const;

    void setDamage(int damage);

    int gerRechargeTime() const;

    void setRechargeTime(int time);

    qreal getAttackRange() const;

    void setAttackRange(qreal range);

    int getHealth() const;

    void setHealth(int health);

};


#endif //AP_PROJ_CHARACTER_H
