#ifndef AP_PROJ_ACTIONATTACK_H
#define AP_PROJ_ACTIONATTACK_H

#include <exception>
#include "Action.h"
#include "Buff.h"
#include "Element.h"


/**
 * When entity X attacks entity Y, we construct an ActionAttack with necessary info,
 * and convey it to entity attacked
 */
class ActionAttack: public Action{

    // damage cause by this attack
    int damage_;

    // buff that the target will get, and duration (if buff is not NONE)
    Buff buff_to_target_ = Buff::NONE;
    int buff_duration_ = 0;

    // element that this attack is infused with
    // may not be added to target, such as Anemo
    Element element_infusion_ = Element::NONE;


public:
    using Action::Action;

    int getDamage() const;

    void setDamage(int damage);

    QPair<Buff, int> getBuff() const;

    void setBuff(Buff buff, int duration);

    Element getElement() const;

    void setElement(Element element);
};

#endif //AP_PROJ_ACTIONATTACK_H
