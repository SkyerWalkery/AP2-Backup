#ifndef AP_PROJ_TOWER_H
#define AP_PROJ_TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class Tower: public QGraphicsPixmapItem{

    int damage_ = 0; // Damage to monster per attack

    int recharge_time_ = 0; // Time (ms) to recharge before an attack

    qreal attack_range_ = 0; // Attack range (px)

public:

    static constexpr const int SunCost = 0; // Cost to build this tower

    Tower(QGraphicsItem *parent = nullptr);

    int getDamage() const;

    void setDamage(int damage);

    int gerRechargeTime() const;

    void setRechargeTime(int time);

    qreal getAttackRange() const;

    void setAttackRange(qreal range);

};


#endif //AP_PROJ_TOWER_H
