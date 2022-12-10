#include "Elf.h"
#include <QGraphicsScene>
#include <QColor>
#include <QPen>
#include <QRandomGenerator>


Elf::Elf(QGraphicsItem *parent) :Character(parent){
    int sz = static_cast<int>(CharacterSize);
    if(sz <= 0)
        throw std::invalid_argument("Character Size not initialized");
    texture_pixmap_ = QPixmap(TEXTURE).scaled(sz, sz);
    setPixmap(texture_pixmap_);

    health_ = max_health_ = 1;
    can_be_attacked_ = false;
    damage_ = 10;
    recharge_time_ = 700; // ms
    attack_range_ = 5;
}

int Elf::type() const {
    return Type;
}

bool Elf::testAreaCond(int cond) {
    return (cond & AreaCond) != 0;
}

void Elf::attack(ActionAttack& action, const QList<Entity*>& candidate_targets) {
    Character::attack(action, candidate_targets);

    auto* target = action.getAcceptor();

    // Add tryAttack visual effect
    auto* attack_effect = new ShootParticle();
    attack_effect->setStartPos(mapToScene(this->boundingRect().center()));
    attack_effect->setEndPos(target->mapToScene(target->boundingRect().center()));
    attack_effect->setZValue(target->zValue()); // Display on top of target
    this->scene()->addItem(attack_effect);
    attack_effect->setSpeed(500);

    // Set element effect
    auto element = Element::NONE;
    auto infusion_buff = getElementInfusionBuff();
    if(infusion_buff != Buff::NONE)
        element = ElementUtil::infusionToElement(infusion_buff);
    attack_effect->setParticleColor(ElementUtil::ElementToParticleColor(element));
    // If infused with anemo, an explosion animation should be appended
    if (element == Element::ANEMO)
        attack_effect->setShouldExplode(true);
    attack_effect->startAnimation();
}

QString Elf::getRandomVoice() const {
    return VOICES[QRandomGenerator::global()->bounded(5)];
}
