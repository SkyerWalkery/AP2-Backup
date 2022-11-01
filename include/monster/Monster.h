#ifndef AP_PROJ_MONSTER_H
#define AP_PROJ_MONSTER_H

#include <QGraphicsPixmapItem>
#include <QPair>


class Monster: public QGraphicsPixmapItem{

    using Direction = QPair<int, int>;

protected:

    Direction direction_ = qMakePair(0, 0);
    qreal speed_ = 10.0; // num of px per second to move
    int health_ = 0;

    static qreal area_size_; // Must be set before construct

public:

    explicit Monster(QGraphicsItem *parent = nullptr);

    qreal getSpeed() const;

    void setSpeed(qreal speed);

    Direction getDirection() const;

    void setDirection(const Direction& direction);

    int getHealth() const;

    void setHealth(int health);

    /*
     * Called by character when it trys to attack.
     * The default implementation only reduce the health
     */
    virtual void attacked(int damage);

    static void setAreaSize(qreal size);
};

#endif //AP_PROJ_MONSTER_H
