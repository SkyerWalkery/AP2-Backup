#include "Grass.h"


Grass::Grass(QGraphicsItem *parent) : Area(parent) {
    setPixmap(QPixmap(TEXTURE));
}

int Grass::type() const {
    return UserType + 1;
}

bool Grass::isOccupied() const {
    return occupied_;
}

void Grass::setOccupied(bool occupied) {
    occupied_ = occupied;
}
