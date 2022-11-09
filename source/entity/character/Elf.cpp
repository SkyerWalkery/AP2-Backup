#include "Elf.h"
#include <QGraphicsScene>


Elf::Elf(QGraphicsItem *parent) :Character(parent){
    int sz = static_cast<int>(CharacterSize);
    if(sz <= 0)
        throw std::invalid_argument("Character Size not initialized");
    setPixmap(QPixmap(TEXTURE).scaled(sz, sz));

    health_ = max_health_ = 1;
    can_be_attacked_ = false;
    damage_ = 1;
    recharge_time_ = 700; // ms
    attack_range_ = 5;
}

int Elf::type() const {
    return Type;
}

bool Elf::testAreaCond(int cond) {
    return (cond & AreaCond) != 0;
}

void Elf::attack(Entity * target) {
    Entity::attack(target);


    // Add attack visual effect
    auto* attack_effect = new MoveCircleParticle(this);
    attack_effect->setStartPos(this->boundingRect().center());
    attack_effect->setEndPos(target->mapToItem(this, target->boundingRect().center()));
    attack_effect->setPen(QPen(Qt::white));
    attack_effect->setBrush(QColor(252, 253, 151));
    attack_effect->setRect(-3, -3, 6, 6);
    attack_effect->setSpeed(500);
    attack_effect->startAnimation();
}
