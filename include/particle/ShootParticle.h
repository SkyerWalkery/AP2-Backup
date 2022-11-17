#ifndef AP_PROJ_MOVINGPARTICLE_H
#define AP_PROJ_MOVINGPARTICLE_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QPropertyAnimation>

/**
 * Visual effect of ranged attack (like a shoot).
 * i.e. A ball that can move toward specific direction
 * e.g. arrow of Elf
 */
class ShootParticle: public QObject, public QGraphicsEllipseItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos_ READ pos WRITE setPos)
    Q_PROPERTY(qreal opacity_ READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal scale_ READ scale WRITE setScale)

    qreal speed_ = 300; // px per second

    QPointF start_pos_;
    QPointF end_pos_;

    // Whether there is phase 2 animation:
    // bullet explodes, and fades at the same time
    bool should_explode_ = false;

public:
    explicit ShootParticle(QGraphicsItem *parent = nullptr);

    enum { Type = UserType + 1001 };
    int type() const override;

    void setSpeed(qreal speed);

    void setStartPos(QPointF pos);
    void setEndPos(QPointF pos);

    void setParticleColor(QColor color);

    void setShouldExplode(bool should_explode);

    void startAnimation();

};

#endif //AP_PROJ_MOVINGPARTICLE_H
