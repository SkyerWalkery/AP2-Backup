#include "Road.h"


const QString Road::TEXTURE = ":/images/mushroom_stem.png";

Road::Road(QGraphicsItem *parent) : Area(parent) {
    setPixmap(QPixmap(TEXTURE));
}
