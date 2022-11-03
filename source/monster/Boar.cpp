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

void Boar::checkImageOrientation() {
    int sz = static_cast<int>(MonsterSize);
    if(sz <= 0)
        throw std::invalid_argument("Monster Size not initialized");

    auto image_pixmap = QPixmap(TEXTURE).scaled(sz, sz);
    QTransform flip_transform;
    flip_transform.scale(-1, 1); // Flip the image
    if(getDirection().first == 1)
        setPixmap(image_pixmap);
    else if(getDirection().first == -1)
        setPixmap(image_pixmap.transformed(flip_transform));
}
