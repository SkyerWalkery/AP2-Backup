#include "ShootParticle.h"
#include <QPen>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

ShootParticle::ShootParticle(QGraphicsItem *parent) : QGraphicsEllipseItem(parent) {
    setPen(QPen(Qt::white));
    setRect(-3, -3, 6, 6);
}

int ShootParticle::type() const {
    return Type;
}

void ShootParticle::setSpeed(qreal speed) {
    if(speed <= 0)
        throw std::invalid_argument("speed cannot be negative");
    speed_ = speed;
}

void ShootParticle::startAnimation() {
    auto *group = new QSequentialAnimationGroup(this);

    auto *move_animation = new QPropertyAnimation(this, "pos_");
    auto dis = qSqrt(qPow(start_pos_.x() - end_pos_.x(), 2) + qPow(start_pos_.y() - end_pos_.y(), 2));
    move_animation->setDuration(static_cast<int>(dis * 1000 / speed_));
    move_animation->setStartValue(start_pos_);
    move_animation->setEndValue(end_pos_);
    group->addAnimation(move_animation);

    // If bullet should explode, add phase 2 animation
    if(should_explode_){
        auto* explode_group = new QParallelAnimationGroup(this);
        int explode_duration = 500;

        auto* scale_animation = new QPropertyAnimation(this, "scale_");
        scale_animation->setDuration(explode_duration);
        scale_animation->setStartValue(1);
        scale_animation->setEndValue(10);
        scale_animation->setEasingCurve(QEasingCurve::OutQuart);
        explode_group->addAnimation(scale_animation);

        auto* fade_animation = new QPropertyAnimation(this, "opacity_");
        fade_animation->setDuration(explode_duration);
        fade_animation->setStartValue(1);
        fade_animation->setEndValue(0);
        fade_animation->setEasingCurve(QEasingCurve::OutQuart);
        explode_group->addAnimation(fade_animation);

        group->addAnimation(explode_group);
    }

    connect(group, &QSequentialAnimationGroup::finished, this, &ShootParticle::deleteLater);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void ShootParticle::setStartPos(QPointF start_pos) {
    start_pos_ = start_pos;
}

void ShootParticle::setEndPos(QPointF end_pos) {
    end_pos_ = end_pos;
}

void ShootParticle::setParticleColor(QColor color) {
    setBrush(color);
}

void ShootParticle::setShouldExplode(bool should_explode) {
    should_explode_ = should_explode;
}
