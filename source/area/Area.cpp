#include "Area.h"

qreal Area::AreaSize = 0;

Area::Area(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    // Without this flag, mouseReleaseEvent would not be called
    // Still don't know why
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void Area::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    // qDebug() << "Press: " << pos().x() << " " << pos().y();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void Area::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    // qDebug() << "Release: " << pos().x() << " " << pos().y();
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

bool Area::isOccupied() const {
    return occupied_;
}

void Area::setOccupied(bool occupied) {
    occupied_ = occupied;
}

int Area::type() const {
    return Type;
}

void Area::setAreaSize(qreal size) {
    AreaSize = size;
}
