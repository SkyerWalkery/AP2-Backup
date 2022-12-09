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

Element ActionAttack::getElement() const {
    return element_infusion_;
}

void ActionAttack::setElement(Element element) {
    element_infusion_ = element;
}

int ActionAttack::getTransmitCnt() const {
    return transmit_cnt_;
}

void ActionAttack::setTransmitCnt(int cnt) {
    transmit_cnt_ = cnt;
}

void ActionAttack::setTextEffect(const QString &text, QColor color) {
    text_effect_ = qMakePair(text, color);
    has_effect_ = true;
}

bool ActionAttack::hasTextEffect() const {
    return has_effect_;
}

const QPair<QString, QColor> &ActionAttack::getTextEffect() const {
    return this->text_effect_;
}
