#include <stdexcept>
#include "ActionAttack.h"

int ActionAttack::getDamage() const {
    return damage_;
}

void ActionAttack::setDamage(int damage) {
    if(damage < 0)
        throw std::invalid_argument("damage cannot be negative");
    damage_ = damage;
}

QPair<Buff, int> ActionAttack::getBuff() const {
    return qMakePair(buff_to_target_, buff_duration_);
}

void ActionAttack::setBuff(Buff buff, int duration) {
    buff_to_target_ = buff;
    buff_duration_ = duration;
}
