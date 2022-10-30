#include "Tower.h"


Tower::Tower(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {

}

int Tower::getDamage() const {
    return damage_;
}

void Tower::setDamage(int damage) {
    damage_ = damage;
}

int Tower::gerRechargeTime() const {
    return recharge_time_;
}

void Tower::setRechargeTime(int time) {
    recharge_time_ = time;
}
