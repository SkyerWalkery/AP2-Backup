#include "ShootParticle.h"

int ShootParticle::type() const {
    return Type;
}

void ShootParticle::setSpeed(qreal speed) {
    if(speed <= 0)
        throw std::invalid_argument("speed cannot be negative");
    speed_ = speed;
}

void ShootParticle::startAnimation() {
    auto *moveAnimation = new QPropertyAnimation(this, "pos_");
    auto dis = qSqrt(qPow(start_pos_.x() - end_pos_.x(), 2) + qPow(start_pos_.y() - end_pos_.y(), 2));
    moveAnimation->setDuration(static_cast<int>(dis * 1000 / speed_));
    moveAnimation->setStartValue(start_pos_);
    moveAnimation->setEndValue(end_pos_);

    connect(moveAnimation, &QPropertyAnimation::finished, this, &ShootParticle::deleteLater);
    moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

}

void ShootParticle::setStartPos(QPointF start_pos) {
    start_pos_ = start_pos;
}

void ShootParticle::setEndPos(QPointF end_pos) {
    end_pos_ = end_pos;
}
