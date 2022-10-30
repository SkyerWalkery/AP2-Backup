#include "Tower.h"


Tower::Tower(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {

}

int Tower::getDamage() const {
    return damage_;
}

void Tower::setDamage(int damage) {
    if(damage <= 0)
        return;
    damage_ = damage;
}

int Tower::gerRechargeTime() const {
    return recharge_time_;
}

void Tower::setRechargeTime(int time) {
    if(time <= 0)
        return;
    recharge_time_ = time;
}

qreal Tower::getAttackRange() const {
    return attack_range_;
}

void Tower::setAttackRange(qreal range) {
    if(range <= 0)
        return;
    attack_range_ = range;
}
