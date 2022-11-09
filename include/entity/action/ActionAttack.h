#ifndef AP_PROJ_ACTIONATTACK_H
#define AP_PROJ_ACTIONATTACK_H

#include <exception>
#include "Action.h"


/*
 * When entity X attacks entity Y, we construct an ActionAttack with necessary info,
 * and convey it to entity attacked
 */
class ActionAttack: public Action{

    // damage cause by this attack
    int damage_;

public:
    using Action::Action;

    int getDamage() const;

    void setDamage(int damage);
};

#endif //AP_PROJ_ACTIONATTACK_H
