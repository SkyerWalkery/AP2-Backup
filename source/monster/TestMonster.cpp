#include "TestMonster.h"

TestMonster::TestMonster(QGraphicsItem *parent) : Monster(parent) {
    int sz = static_cast<int>(area_size_);
    if(sz <= 0)
        throw std::invalid_argument("Area Size not initialized");
    setPixmap(QPixmap(TEXTURE).scaled(sz, sz));
    speed_ = 25;
    health_ = 10;
}

int TestMonster::type() const {
    return Type;
}
