#include "area/Area.h"

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
