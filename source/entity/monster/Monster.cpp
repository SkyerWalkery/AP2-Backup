#include "Monster.h"
#include <QPen>

qreal Monster::MonsterSize = 0;

Monster::Monster(QGraphicsItem *parent) : Entity(parent) {
    attack_range_ = 1; // Monster's tryAttack range is 1 block by default
    can_be_attacked_ = true;
    setZValue(2);

    health_bar_ = new QGraphicsRectItem(0, 0, MonsterSize, 4, this);
    health_bar_->setPen(QPen(Qt::transparent));
    health_bar_->setBrush(QBrush(Qt::transparent));
    //updateHealthBar();
}

QColor Monster::getHealthBarColor() const {
    // Color of health bar
    // color[i] is color when health is between {i * (1/max)} and {(i+1) * (1/max)}
    static QList<QColor> HealthBarColor = {
            QColor(255, 0, 0),
            QColor(255, 128, 0),
            QColor(255, 255, 0),
            QColor(128, 255, 0),
            QColor(0, 255, 0)
    };
    // If health is at max, set health bar as invisible
    if(health_ >= max_health_)
        return Qt::transparent;
    return HealthBarColor[getHealth() * HealthBarColor.size() / getMaxHealth()];
}

void Monster::updateHealthBar() {
    // No damage taken until now, don't show health bar
    if(getHealth() == getMaxHealth())
        return;
    // Set color accordingly
    auto pen = health_bar_->pen();
    pen.setColor(Qt::white);
    auto brush = health_bar_->brush();
    brush.setColor(getHealthBarColor());
    health_bar_->setBrush(brush);
    health_bar_->setPen(pen);

    // Set length of bar
    qreal bar_len = MonsterSize * getHealth() / getMaxHealth();
    health_bar_->setRect(0, 0, bar_len, 4);
}

qreal Monster::getSpeed() const {
    qreal real_speed = speed_;
    // If buff exists...
    // Pay attention to sequence of if-clauses
    if(buffs_.contains(Buff::WINDFALL))
        real_speed += speed_ / 3; // Speed increases by 30%
    if(buffs_.contains(Buff::FROZEN))
        real_speed = 0; // If frozen, speed would be 0 even when having a speed increase

    return real_speed;
}

void Monster::setSpeed(qreal speed) {
    if(speed < 0.0)
        return;
    speed_ = speed;
}

Monster::Direction Monster::getDirection() const {
    return direction_;
}

void Monster::setDirection(const Monster::Direction &direction) {
    direction_ = direction;
    // Set orientation according to monster's moving direction
    if((direction_.first == -1) ^ is_horizontally_flipped_)
        flipHorizontally();
}

void Monster::setMonsterSize(qreal size) {
    MonsterSize = size;
}

void Monster::updateStatus() {
    Entity::updateStatus();
    updateHealthBar();
}
