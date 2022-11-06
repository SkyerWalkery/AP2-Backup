#include "Character.h"

qreal Character::CharacterSize = 0;

Character::Character(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {

}

int Character::getDamage() const {
    return damage_;
}

void Character::setDamage(int damage) {
    if(damage <= 0)
        return;
    damage_ = damage;
}

int Character::gerRechargeTime() const {
    return recharge_time_;
}

void Character::setRechargeTime(int time) {
    if(time <= 0)
        return;
    recharge_time_ = time;
}

qreal Character::getAttackRange() const {
    return attack_range_;
}

void Character::setAttackRange(qreal range) {
    if(range <= 0)
        return;
    attack_range_ = range;
}

int Character::getHealth() const {
    return health_;
}

void Character::setHealth(int health) {
    health_ = health;
}

void Character::setCharacterSize(qreal size) {
    CharacterSize = size;
}

bool Character::inAttackRange(Monster* target) const {
    auto pos = target->scenePos();
    auto this_pos = scenePos();
    qreal distance = qSqrt(qPow(this_pos.x() - pos.x(), 2) + qPow(this_pos.y() - pos.y(), 2));
    return distance <= getAttackRange() * CharacterSize;
}

bool Character::readyToAttack() const {
    return recharged_ >= recharge_time_;
}

void Character::recharge(int time) {
    recharged_ += time;
}

void Character::attack(Monster* monster) {
    if(!monster || !readyToAttack())
        return;

    recharged_ %= recharge_time_;
    monster->attacked(getDamage());
    qDebug() << "Attack " << monster->getHealth();
}

