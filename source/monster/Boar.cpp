#include "Boar.h"

Boar::Boar(QGraphicsItem *parent) : Monster(parent) {
    int sz = static_cast<int>(MonsterSize);
    if(sz <= 0)
        throw std::invalid_argument("Monster Size not initialized");
    setPixmap(QPixmap(TEXTURE).scaled(sz, sz));
    speed_ = 25;
    health_ = 10;
}

int Boar::type() const {
    return Type;
}
