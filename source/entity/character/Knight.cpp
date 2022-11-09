#include "Knight.h"

Knight::Knight(QGraphicsItem *parent) :Character(parent){
    int sz = static_cast<int>(CharacterSize);
    if(sz <= 0)
        throw std::invalid_argument("Character Size not initialized");
    texture_pixmap_ = QPixmap(TEXTURE).scaled(sz, sz);
    setPixmap(texture_pixmap_);

    health_ = max_health_ = 10;
    can_be_attacked_ = true;
    damage_ = 2;
    recharge_time_ = 500; // ms
    attack_range_ = 1;
}

int Knight::type() const {
    return Type;
}

bool Knight::testAreaCond(int cond) {
    return (cond & AreaCond) != 0;
}
