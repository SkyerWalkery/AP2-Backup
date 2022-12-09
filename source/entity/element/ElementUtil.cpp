#include "ElementUtil.h"
#include "BuffUtil.h"
#include <stdexcept>
#include <QString>

QColor ElementUtil::ElementToParticleColor(Element element) {
    switch (element) {
        case Element::NONE:
            return {252, 253, 151};
        case Element::ANEMO:
            return {106, 254, 218};
        case Element::CRYO:
            return {150, 255, 255};
        case Element::HYDRO:
            return {40, 214, 251};
        case Element::PYRO:
            return {255, 155, 4};
        default:
            throw std::invalid_argument("No matching particle color for element");
    }
}

Element ElementUtil::infusionToElement(Buff buff) {
    switch (buff) {
        case Buff::INFUSION_ANEMO:
            return Element::ANEMO;
        case Buff::INFUSION_CRYO:
            return Element::CRYO;
        case Buff::INFUSION_HYDRO:
            return Element::HYDRO;
        case Buff::INFUSION_PYRO:
            return Element::PYRO;
        default:
            throw std::invalid_argument("No matching element for infusion buff");
    }
}

void ElementUtil::makeElementReaction(Element aura, ActionAttack &action) {
    // Not enough elements (at least one)
    if(aura == Element::NONE || action.getElement() == Element::NONE || aura == action.getElement())
        return;

    switch(aura){
        case Element::PYRO:{
            switch(action.getElement()){
                case Element::HYDRO:{
                    action.setDamage(action.getDamage() * 2);
                    action.setTextEffect("Vaporize", QColor(246, 208, 112));
                } break; // Vaporize (2× DMG)
                case Element::CRYO:{
                    action.setDamage(action.getDamage() * 3 / 2);
                    action.setTextEffect("Melt", QColor(246, 208, 112));
                } break; // Reverse Melt (1.5× DMG)
                case Element::ANEMO:{
                    action.setTransmitCnt(2);
                    action.setElement(aura);
                    action.setTextEffect("Swirl", ElementToParticleColor(Element::ANEMO));
                } break; // Swirl (range damage and elemental absorption)
                default:
                    break;
            }
        }

        case Element::HYDRO:{
            switch(action.getElement()){
                case Element::PYRO:{
                    action.setDamage(action.getDamage() * 3 / 2);
                    action.setTextEffect("Vaporize", QColor(246, 208, 112));
                } break; // Reverse Vaporize (1.5× DMG)
                case Element::CRYO:{
                    action.setBuff(Buff::FROZEN, static_cast<int>(0.5 * 1000));
                    action.setTextEffect("Frozen", BuffUtil::buffToColor(Buff::FROZEN));
                } break; // Frozen
                case Element::ANEMO:{
                    action.setTransmitCnt(2);
                    action.setElement(aura);
                    action.setTextEffect("Swirl", ElementToParticleColor(Element::ANEMO));
                } break; // Swirl
                default:
                    break;
            }
        }

        case Element::CRYO:{
            switch(action.getElement()){
                case Element::PYRO:{
                    action.setDamage(action.getDamage() * 2);
                    action.setTextEffect("Melt", QColor(246, 208, 112));
                } break; // Melt (2× DMG)
                case Element::HYDRO:{
                    action.setBuff(Buff::FROZEN, static_cast<int>(0.5 * 1000));
                    action.setTextEffect("Frozen", BuffUtil::buffToColor(Buff::FROZEN));
                } break; // Frozen
                case Element::ANEMO:{
                    action.setTransmitCnt(2);
                    action.setElement(aura);
                    action.setTextEffect("Swirl", ElementToParticleColor(Element::ANEMO));
                } break; // Swirl
                default:
                    break;
            }
        }

        default:
            break;
    }

}
