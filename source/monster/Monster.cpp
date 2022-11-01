#include "Monster.h"

qreal Monster::area_size_ = 0;

Monster::Monster(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

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
}

int Monster::getHealth() const {
    return health_;
}

void Monster::setHealth(int health) {
    health_ = health;
}

void Monster::attacked(int damage) {
    setHealth(getHealth() - damage);
}

void Monster::setAreaSize(qreal size) {
    area_size_ = size;
}
