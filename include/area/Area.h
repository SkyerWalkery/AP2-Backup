#ifndef AP_PROJ_AREA_H
#define AP_PROJ_AREA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class Area: public QGraphicsPixmapItem{

    // If this area has a character or other objects
    bool occupied_ = false;

public:
    explicit Area(QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    bool isOccupied() const;

    void setOccupied(bool occupied);
};

#endif //AP_PROJ_AREA_H
