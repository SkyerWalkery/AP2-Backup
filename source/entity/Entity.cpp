#include "Entity.h"
#include <QRandomGenerator>

qreal Entity::AreaSize = 0;

int Entity::GameRefreshInterval = 0;

Entity::Entity(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    // Check if some static members are initialized correctly
    if(AreaSize <= 0)
        throw std::runtime_error("Entity: AreaSize not initialized correctly");
    if(GameRefreshInterval <= 0)
        throw std::runtime_error("Entity: GameRefreshInterval not initialized correctly");
}

int Entity::getDamage() const {
    int real_damage = damage_;
    // If buff exists...
    if(buffs_.contains(Buff::WOLF_S_GRAVESTONE))
        real_damage += damage_ / 3; // Damage increase by 30%

    return real_damage;
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
    // Health is 0 at least
    // negative value will lead to various problems among code
    return qMax(health_, 0);
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

void Entity::setRefreshInterval(int interval) {
    GameRefreshInterval = interval;
}

bool Entity::inAttackRange(Entity* target) const {
    qreal distance = distanceBetween(scenePos(), target->scenePos());
    return distance <= getAttackRange() * AreaSize;
}

bool Entity::readyToAttack() const {
    return recharged_ >= recharge_time_;
}

void Entity::recharge() {
    int recharged_val = GameRefreshInterval;
    // If buff exists...
    if(buffs_.contains(Buff::WOLF_S_GRAVESTONE))
        recharged_val += GameRefreshInterval / 3; // Damage speed increase by 30%
    if(buffs_.contains(Buff::FROZEN))
        recharged_val = 0; // Cannot attack at all

    recharged_ += recharged_val;
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
        ActionAttack attack(this, target);
        this->attack(attack);
    }
}

void Entity::attack(ActionAttack& action) {
    if(auto* target = action.getAcceptor(); target != nullptr) {
        recharged_ %= recharge_time_;
        action.setDamage(getDamage());
        // Add buff if needed
        if(this->hasBuff(Buff::INFUSION_FROZEN)) {
            // Each attack has 30% of probability of freezing target
            // 0.5s of frozen status by default
            int randint = QRandomGenerator::global()->bounded(100);
            if(randint < 30)
                action.setBuff(Buff::FROZEN, static_cast<int>(0.5 * 1000));
        }
        target->attacked(action);
    }
}

void Entity::attacked(ActionAttack& action) {
    // Receive damage from attack
    int damage = action.getDamage();
    setHealth(getHealth() - damage);

    // attack may carry a buff
    auto [buff, duration] = action.getBuff();
    if(buff != Buff::NONE)
        this->addBuff(buff, duration);
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

void Entity::manageBuff() {
    auto buff_it = buffs_.begin();
    while(buff_it != buffs_.end()){
        buff_it.value() -= GameRefreshInterval;
        // time up for this buff
        if(buff_it.value() <= 0)
            buff_it = buffs_.erase(buff_it);
        else
            ++buff_it;
    }
}

void Entity::addBuff(Buff buff, int duration) {
    buffs_[buff] = buffs_.value(buff, 0) + duration;
}

bool Entity::hasBuff(Buff buff) const {
    return buffs_.contains(buff);
}
