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
