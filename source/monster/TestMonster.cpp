#include "TestMonster.h"

TestMonster::TestMonster(QGraphicsItem *parent) : Monster(parent) {
    setPixmap(QPixmap(TEXTURE));
    speed_ = 25;
    health_ = 10;
}

int TestMonster::type() const {
    return Type;
}
