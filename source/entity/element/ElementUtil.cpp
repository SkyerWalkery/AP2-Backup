#include "ElementUtil.h"
#include <stdexcept>

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
