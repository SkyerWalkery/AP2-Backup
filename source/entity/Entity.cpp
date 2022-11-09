#include "Entity.h"

qreal Entity::AreaSize = 0;

int Entity::getDamage() const {
    return damage_;
}

void Entity::setDamage(int damage) {
    if(damage <= 0)
        return;
    damage_ = damage;
}

int Entity::gerRechargeTime() const {
    return recharge_time_;
}

void Entity::setRechargeTime(int time) {
    if(time <= 0)
        return;
    recharge_time_ = time;
}

qreal Entity::getAttackRange() const {
    return attack_range_;
}

void Entity::setAttackRange(qreal range) {
    if(range <= 0)
        return;
    attack_range_ = range;
}

int Entity::getHealth() const {
    return health_;
}

void Entity::setHealth(int health) {
    health_ = health;
}

int Entity::getMaxHealth() const {
    return max_health_;
}

bool Entity::canBeAttacked() const {
    return can_be_attacked_;
}

void Entity::setAreaSize(qreal size) {
    AreaSize = size;
}

bool Entity::inAttackRange(Entity* target) const {
    qreal distance = distanceBetween(scenePos(), target->scenePos());
    return distance <= getAttackRange() * AreaSize;
}

bool Entity::readyToAttack() const {
    return recharged_ >= recharge_time_;
}

void Entity::recharge(int time) {
    recharged_ += time;
}

bool Entity::isAlive() const {
    return getHealth() > 0;
}

void Entity::tryAttack(const QList<Entity*>& targets) {
    if(!readyToAttack())
        return;

    // Check if any entity is in tryAttack range
    // If so, choose the nearest one
    qreal min_dis = 99999999;
    Entity* target = nullptr;
    for(auto* entity: targets){
        if(!entity->isAlive() || !entity->canBeAttacked() || !inAttackRange(entity))
            continue;
        auto dis = distanceBetween(scenePos(),entity->scenePos());
        if(dis < min_dis){
            min_dis = dis;
            target = entity;
        }
    }
    if(target) {
        this->attack(target);
    }
}

void Entity::attack(Entity *target) {
    if(!readyToAttack())
        return;
    if(target) {
        recharged_ %= recharge_time_;
        ActionAttack attack(this, target);
        attack.setDamage(getDamage());
        target->attacked(attack);
    }
}

void Entity::attacked(const ActionAttack& action) {
    int damage = action.getDamage();
    setHealth(getHealth() - damage);
}

qreal Entity::distanceBetween(const QPointF &p1, const QPointF &p2) {
    return qSqrt(qPow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2));
}

void Entity::flipHorizontally() {
    QTransform flip_transform;
    flip_transform.scale(-1, 1);
    texture_pixmap_ = texture_pixmap_.transformed(flip_transform);
    setPixmap(texture_pixmap_);
    is_horizontally_flipped_ = !is_horizontally_flipped_;
}
