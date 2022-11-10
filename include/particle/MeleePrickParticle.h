#ifndef AP_PROJ_MELEEPRICKPARTICLE_H
#define AP_PROJ_MELEEPRICKPARTICLE_H

#include <QGraphicsLineItem>
#include <QObject>
#include <QPropertyAnimation>

/*
 * Visual effect of melee attack.
 * i.e. A line that can move forward / backward (prick) or "sweep"
 * e.g. attack of Knight
 */
class MeleePrickParticle: public QObject, public QGraphicsLineItem{
    Q_OBJECT
    Q_PROPERTY(QLineF line_ READ line WRITE setLine)

    qreal speed_ = 600; // px per second

    QPointF attacker_pos_;
    QPointF target_pos_;

public:
    using QGraphicsLineItem::QGraphicsLineItem;

    enum { Type = UserType + 1002 };
    int type() const override;

    void setSpeed(qreal speed);

    void setAttackerPos(QPointF attacker_pos);

    void setTargetPos(QPointF target_pos);

    void startAnimation();

};

#endif //AP_PROJ_MELEEPRICKPARTICLE_H
