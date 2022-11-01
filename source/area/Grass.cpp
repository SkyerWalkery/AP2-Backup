#include "Grass.h"


Grass::Grass(QGraphicsItem *parent) : Area(parent) {
    int sz = static_cast<int>(area_size_);
    if(sz <= 0)
        throw std::invalid_argument("Area Size not initialized");
    setPixmap(QPixmap(TEXTURE).scaled(sz, sz));
}

int Grass::type() const {
    return Type;
}
