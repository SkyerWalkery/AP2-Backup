#include "Grass.h"


const QString Grass::TEXTURE = ":/images/black_stained_glass.png";

Grass::Grass(QGraphicsItem *parent) : Area(parent) {
    setPixmap(QPixmap(TEXTURE));
}
