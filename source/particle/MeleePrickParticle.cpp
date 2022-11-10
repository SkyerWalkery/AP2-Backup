#include "MeleePrickParticle.h"

int MeleePrickParticle::type() const {
    return Type;
}

void MeleePrickParticle::startAnimation() {
    auto *prick_animation = new QPropertyAnimation(this, "line_");
    auto dis = qSqrt(qPow(attacker_pos_.x() - target_pos_.x(), 2) + qPow(attacker_pos_.y() - target_pos_.y(), 2));
    auto duration = static_cast<int>(dis * 1000 / speed_);
    prick_animation->setDuration(duration);

    auto start_end_line = QLineF(
            attacker_pos_,
            attacker_pos_ + (target_pos_ - attacker_pos_) * 3 / 4
            );
    auto key_line = QLineF(
            attacker_pos_ + (target_pos_ - attacker_pos_) * 1 / 4,
            target_pos_
    );

    prick_animation->setStartValue(start_end_line);
    prick_animation->setKeyValueAt(0.5, key_line);
    prick_animation->setEndValue(start_end_line);

    connect(prick_animation, &QPropertyAnimation::finished, this, &MeleePrickParticle::deleteLater);
    prick_animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MeleePrickParticle::setAttackerPos(QPointF attacker_pos) {
    attacker_pos_ = attacker_pos;
}

void MeleePrickParticle::setTargetPos(QPointF target_pos) {
    target_pos_ = target_pos;
}

void MeleePrickParticle::setSpeed(qreal speed) {
    if(speed <= 0)
        throw std::invalid_argument("speed cannot be negative");
    speed_ = speed;
}
