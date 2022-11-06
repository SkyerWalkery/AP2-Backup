#include "Entity.h"

qreal Entity::AreaSize = 0;

int Entity::getDamage() const {
    return damage_;
}

void Entity::setDamage(int damage) {
    if(damage <= 0)
        return;
    damage_ = damage;
}

int Entity::gerRechargeTime() const {
    return recharge_time_;
}

void Entity::setRechargeTime(int time) {
    if(time <= 0)
        return;
    recharge_time_ = time;
}

qreal Entity::getAttackRange() const {
    return attack_range_;
}

void Entity::setAttackRange(qreal range) {
    if(range <= 0)
        return;
    attack_range_ = range;
}

int Entity::getHealth() const {
    return health_;
}

void Entity::setHealth(int health) {
    health_ = health;
}

void Entity::setAreaSize(qreal size) {
    AreaSize = size;
}

bool Entity::inAttackRange(Entity* target) const {
    auto pos = target->scenePos();
    auto this_pos = scenePos();
    qreal distance = qSqrt(qPow(this_pos.x() - pos.x(), 2) + qPow(this_pos.y() - pos.y(), 2));
    return distance <= getAttackRange() * AreaSize;
}

bool Entity::readyToAttack() const {
    return recharged_ >= recharge_time_;
}

void Entity::recharge(int time) {
    recharged_ += time;
}

bool Entity::isAlive() const {
    return getHealth() > 0;
}

void Entity::attack(Entity* target) {
    if(!target || !readyToAttack())
        return;

    recharged_ %= recharge_time_;
    target->attacked(getDamage());
    qDebug() << "Attack " << target->getHealth();
}

void Entity::attacked(int damage) {
    setHealth(getHealth() - damage);
}

