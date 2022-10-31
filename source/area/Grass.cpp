#include "Grass.h"


Grass::Grass(QGraphicsItem *parent) : Area(parent) {
    setPixmap(QPixmap(TEXTURE));
}

int Grass::type() const {
    return Type;
}
