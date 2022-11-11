#include "Knight.h"
#include "MeleePrickParticle.h"
#include <QPen>

Knight::Knight(QGraphicsItem *parent) :Character(parent){
    int sz = static_cast<int>(CharacterSize);
    if(sz <= 0)
        throw std::invalid_argument("Character Size not initialized");
    texture_pixmap_ = QPixmap(TEXTURE).scaled(sz, sz);
    setPixmap(texture_pixmap_);

    health_ = max_health_ = 100;
    can_be_attacked_ = true;
    damage_ = 15;
    recharge_time_ = 500; // ms
    attack_range_ = 1;
}

int Knight::type() const {
    return Type;
}

bool Knight::testAreaCond(int cond) {
    return (cond & AreaCond) != 0;
}

void Knight::attack(ActionAttack& action) {
    Character::attack(action);

    auto* target = action.getAcceptor();

    // Add tryAttack visual effect
    auto* attack_effect = new MeleePrickParticle(this);
    attack_effect->setAttackerPos(this->boundingRect().center());
    attack_effect->setTargetPos(target->mapToItem(this, target->boundingRect().center()));
    QPen pen(QColor(255, 255, 51));
    pen.setWidth(5);
    pen.setCapStyle(Qt::RoundCap);
    attack_effect->setPen(pen);
    attack_effect->setSpeed(300);
    attack_effect->startAnimation();
}
