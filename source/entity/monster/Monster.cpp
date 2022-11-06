#include "Monster.h"

qreal Monster::MonsterSize = 0;

Monster::Monster(QGraphicsItem *parent) : Entity(parent) {
    // Monster's attack range is 1 block by default
    attack_range_ = 1;
    can_be_attacked_ = true;
    setZValue(2);
}

void Monster::checkImageOrientation() {
    // Do nothing here
}

qreal Monster::getSpeed() const {
    return speed_;
}

void Monster::setSpeed(qreal speed) {
    if(speed < 0.0)
        return;
    speed_ = speed;
}

Monster::Direction Monster::getDirection() const {
    return direction_;
}

void Monster::setDirection(const Monster::Direction &direction) {
    direction_ = direction;
    checkImageOrientation();
}

void Monster::setMonsterSize(qreal size) {
    MonsterSize = size;
}
