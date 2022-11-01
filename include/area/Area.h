#ifndef AP_PROJ_AREA_H
#define AP_PROJ_AREA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class Area: public QGraphicsPixmapItem{

protected:

    // If this area has a character or other objects
    bool occupied_ = false;

    static qreal area_size_; // Must be set before construct

public:
    explicit Area(QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    bool isOccupied() const;

    void setOccupied(bool occupied);

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 1 };
    int type() const override;

    static void setAreaSize(qreal size);
};

#endif //AP_PROJ_AREA_H
