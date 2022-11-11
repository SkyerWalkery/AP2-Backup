#include "Boar.h"

Boar::Boar(QGraphicsItem *parent) : Monster(parent) {
    int sz = static_cast<int>(MonsterSize);
    if(sz <= 0)
        throw std::invalid_argument("Monster Size not initialized");
    texture_pixmap_ = QPixmap(TEXTURE).scaled(sz, sz);
    setPixmap(texture_pixmap_);

    // Set entity attributes
    damage_ = 10;
    recharge_time_ = 800;
    speed_ = 25;
    health_ = max_health_ = 100;
}

int Boar::type() const {
    return Type;
}
