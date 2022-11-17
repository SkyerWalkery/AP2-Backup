#include "Character.h"

qreal Character::CharacterSize = 0;

void Character::setCharacterSize(qreal size) {
    CharacterSize = size;
}

void Character::attack(ActionAttack& action, const QList<Entity*>& candidate_targets) {
    Entity::attack(action, candidate_targets);

    auto* target = action.getAcceptor();
    // When try to tryAttack a monster at self's left
    // Orientation of texture should be flipped
    bool at_left = target->mapToItem(this, QPointF(0, 0)).x() < 0;
    if(at_left ^ is_horizontally_flipped_)
        flipHorizontally();
}
