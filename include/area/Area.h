#ifndef AP_PROJ_AREA_H
#define AP_PROJ_AREA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class Area: public QGraphicsPixmapItem{
public:
    explicit Area(QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif //AP_PROJ_AREA_H
