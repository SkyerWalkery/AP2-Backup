#include "Entity.h"
#include "SimpleTextParticle.h"
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
        real_damage += damage_ * 3; // Damage increase by 30%

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
        this->attack(attack, targets);
    }
}

void Entity::attack(ActionAttack& action, const QList<Entity*>& candidate_targets) {
    if(auto* target = action.getAcceptor(); target != nullptr) {
        recharged_ %= recharge_time_;
        action.setDamage(getDamage());

        // Add buff if needed
        // Target has 30% probability of getting a de-buff
        // Each de-buff shares this 30% equally
        auto* random = QRandomGenerator::global();
        if(random->bounded(100) < 30) {
            QList<QPair<Buff, int>> candidates; // candidate buffs (with duration) that may be attached to target
            if (this->hasBuff(Buff::INFUSION_FROZEN))
                candidates.push_back(qMakePair(Buff::FROZEN, static_cast<int>(0.5 * 1000)));
            if (this->hasBuff(Buff::CAUSE_CORROSION))
                candidates.push_back(qMakePair(Buff::CORRODED, static_cast<int>(5 * 1000)));
            // add de-buff to action
            if(!candidates.empty()) {
                auto&[buff, duration] = candidates[random->bounded(candidates.size())];
                action.setBuff(buff, duration);
            }
        }

        // Add element infusion if needed
        if(this->hasBuff(Buff::INFUSION_ANEMO))
            action.setElement(Element::ANEMO);
        else if(this->hasBuff(Buff::INFUSION_CRYO))
            action.setElement(Element::CRYO);
        else if(this->hasBuff(Buff::INFUSION_HYDRO))
            action.setElement(Element::HYDRO);
        else if(this->hasBuff(Buff::INFUSION_PYRO))
            action.setElement(Element::PYRO);

        // TODO: Move set cnt to element reaction
        if(this->hasBuff(Buff::INFUSION_ANEMO))
            action.setTransmitCnt(2);
        else
            action.setTransmitCnt(1);

        target->attacked(action, candidate_targets);
    }
}

void Entity::attacked(ActionAttack& action, const QList<Entity*>& candidate_targets) {
    // Receive damage from attack
    int damage = action.getDamage();
    setHealth(getHealth() - damage);

    // Element reaction
    if(element_aura_ == Element::NONE && ElementUtil::canApplyAura(action.getElement())){
        element_aura_ = action.getElement();
    }
    else if(action.getElement() != Element::NONE /* and element_aura_ is not Element::NONE */){
        bool has_react = ElementUtil::makeElementReaction(element_aura_, action);
        if(has_react)
            element_aura_ = Element::NONE;
    }

    // Attack may carry a buff
    auto [buff, duration] = action.getBuff();
    if(buff != Buff::NONE) {
        this->addBuff(buff, duration);
        // Add visual effect of buff
        auto *buff_effect = new SimpleTextParticle(BuffUtil::buffToString(buff), this);
        buff_effect->setTextColor(BuffUtil::buffToColor(buff));
        buff_effect->startAnimation();
    }

    // Attack may carry text effect
    if(action.hasTextEffect()){
        auto *text_effect = new SimpleTextParticle(action.getTextEffect().first, this);
        text_effect->setTextColor(action.getTextEffect().second);
        text_effect->startAnimation();
    }

    // Consider range attack
    // If damage transmit counter > 0 (after decrease), attack is turned into AOE
    action.setTransmitCnt(action.getTransmitCnt() - 1);
    if(action.getTransmitCnt() > 0){
        // AOE is done below
        // Iterate candidate targets, create new attack to those near self
        for(auto* candidate_target: candidate_targets){
            if(candidate_target == this)
                continue;
            if(distanceBetween(scenePos(), candidate_target->scenePos()) <= AreaSize){
                // attacker is the origin one that has attacked self
                ActionAttack aoe(action.getInitiator(), candidate_target);
                aoe.setTransmitCnt(action.getTransmitCnt() - 1);
                //  aoe damage is one-third of origin damage by default
                aoe.setDamage(action.getDamage() / 3);
                aoe.setElement(action.getElement());
                // No buff
                candidate_target->attacked(aoe, candidate_targets);
            }
        }
    }
}

void Entity::updateStatus() {
    manageBuff();
    doContinuousExtraDamage();
    recharge();
}

void Entity::doContinuousExtraDamage() {
    int damage_rate = 0;
    if(buffs_.contains(Buff::CORRODED))
        damage_rate += 10; // Corrosion does 10 damage per second

    // No damage is taken
    if(damage_rate == 0){
        continuous_extra_damage_counter_ = 0;
        return;
    }
    continuous_extra_damage_counter_ += GameRefreshInterval;
    if(continuous_extra_damage_counter_ < 1000)
        return;

    int num_damage = continuous_extra_damage_counter_ / 1000;
    continuous_extra_damage_counter_ %= 1000;
    setHealth(getHealth() - num_damage * damage_rate);
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
    if(hasBuff(buff)) {
        buffs_[buff] += duration;
        return;
    }

    // An entity can have 2 buffs at most (de-buff not included)
    int num_buff = static_cast<int>(buffs_.size());
    for(auto key = buffs_.keyBegin(); key != buffs_.keyEnd(); ++key){
        if(BuffUtil::isDeBuff(*key))
            --num_buff;
    }
    if(num_buff >= 2)
        return;

    // An entity can have at most one infusion buff at the same time
    if(getElementInfusionBuff() != Buff::NONE && BuffUtil::isInfusionBuff(buff))
        return;

    buffs_[buff] = duration;
}

void Entity::removeBuff(Buff buff) {
    // If buff doesn't exist in buffs_, QHash::remove would return false
    buffs_.remove(buff);
}

bool Entity::hasBuff(Buff buff) const {
    return buffs_.contains(buff);
}

Buff Entity::getElementInfusionBuff() const {
    auto ret = Buff::NONE;
    for(auto buff = buffs_.keyBegin(); buff != buffs_.keyEnd(); ++buff) {
        if(BuffUtil::isInfusionBuff(*buff)) {
            ret = *buff;
            break; // An entity can have at most one infusion buff at the same time
        }
    }
    return ret;
}
