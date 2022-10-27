#include "Monster.h"


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
