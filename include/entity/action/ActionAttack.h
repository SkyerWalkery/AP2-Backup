#ifndef AP_PROJ_ACTIONATTACK_H
#define AP_PROJ_ACTIONATTACK_H

#include <exception>
#include "Action.h"
#include "Buff.h"
#include "ElementUtil.h"


/**
 * When entity X attacks entity Y, we construct an ActionAttack with necessary info,
 * and convey it to entity attacked
 */
class ActionAttack: public Action{

    // damage cause by this attack
    int damage_;

    // times of this attack can be transmitted
    // When an entity is attacked, entities around get attacked too (range attack),
    // the former "transmits" damage to entities around,
    // and during the process this counter should decrease by one.
    // If counter is 0, do nothing in Entity::attack()
    int transmit_cnt_ = 1;

    // buff that the target will get, and duration (if buff is not NONE)
    Buff buff_to_target_ = Buff::NONE;
    int buff_duration_ = 0;

    // element that this attack is infused with
    // may not be added to target, such as Anemo
    Element element_infusion_ = Element::NONE;

    // Attributes of text effect: { text displayed, text color }
    // Used in element reactions
    QPair<QString, QColor> text_effect_;
    bool has_effect_ = false;


public:
    using Action::Action;

    int getDamage() const;

    void setDamage(int damage);

    QPair<Buff, int> getBuff() const;

    void setBuff(Buff buff, int duration);

    Element getElement() const;

    void setElement(Element element);

    int getTransmitCnt() const;

    void setTransmitCnt(int cnt);

    void setTextEffect(const QString& text, QColor color);

    bool hasTextEffect() const;

    const QPair<QString, QColor>& getTextEffect() const;
};

#endif //AP_PROJ_ACTIONATTACK_H
