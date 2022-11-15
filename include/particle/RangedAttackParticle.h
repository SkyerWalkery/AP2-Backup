#ifndef AP_PROJ_MOVINGPARTICLE_H
#define AP_PROJ_MOVINGPARTICLE_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPropertyAnimation>

/**
 * Visual effect of ranged attack.
 * i.e. A ball that can move toward specific direction
 * e.g. arrow of Elf
 */
class RangedAttackParticle: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos_ READ pos WRITE setPos)

    qreal speed_ = 300; // px per second

    QPointF start_pos_;
    QPointF end_pos_;

public:
    using QGraphicsEllipseItem::QGraphicsEllipseItem;

    enum { Type = UserType + 1001 };
    int type() const override;

    void setSpeed(qreal speed);

    void setStartPos(QPointF pos);
    void setEndPos(QPointF pos);

    void startAnimation();

};

#endif //AP_PROJ_MOVINGPARTICLE_H
