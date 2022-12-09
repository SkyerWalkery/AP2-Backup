#ifndef AP_PROJ_ELEMENTUTIL_H
#define AP_PROJ_ELEMENTUTIL_H

#include <QColor>
#include <QString>
#include "Element.h"
#include "Buff.h"
// #include "ActionAttack.h"
class ActionAttack;

/**
 * Utility for element system
 */
class ElementUtil{

    static constexpr const char* ICON_ANEMO = ":/icons/element_anemo.png";
    static constexpr const char* ICON_PYRO = ":/icons/element_pyro.png";
    static constexpr const char* ICON_HYDRO = ":/icons/element_hydro.png";
    static constexpr const char* ICON_CRYO = ":/icons/element_cryo.png";

public:

    /**
     * Returns particle color when infused with given color
     */
    static QColor ElementToParticleColor(Element element);

    /**
     * Returns file name of icon of element
     */
    static QString elementToIcon(Element element);

    /**
     * Returns element that infusion buff will attach to attack
     * e.g. If a character has buff "INFUSION_HYDRO", this method returns element "HYDRO"
     */
    static Element infusionToElement(Buff buff);

    /**
     * Make an element reaction if possible.
     * `action` would be changed to carry impacts of a reaction.<BR>
     * e.g.
     * Vaporize will multiply damage by 2 or 1.5,
     * and info of reaction text effect would be added.
     * <BR>
     * Element reactions available are listed below (made by https://ozh.github.io/ascii-tables/)
     * +----------------+-------------------------------+---------------------+---------------------------+--------+
     * | Aura\Infusion  |  Pyro                         |  Hydro              |  Cryo                     |  Anemo |
     * +----------------+-------------------------------+---------------------+---------------------------+--------+
     * | Pyro           |                               |  Vaporize (2× DMG)  |  Reverse Melt (1.5× DMG)  |  Swirl |
     * +----------------+-------------------------------+---------------------+---------------------------+--------+
     * | Hydro          |  Reverse Vaporize (1.5× DMG)  |                     |  Frozen                   |  Swirl |
     * +----------------+-------------------------------+---------------------+---------------------------+--------+
     * | Cryo           |  Melt (2× DMG)                |  Frozen             |                           |  Swirl |
     * +----------------+-------------------------------+---------------------+---------------------------+--------+
     *
     * @param aura element carried by the target
     * @param action attack action made by attacker, serving as both parameter and part of returned value
     * @return if an reaction happens
     */
    static bool makeElementReaction(Element aura, ActionAttack& action);

    /**
     * Returns if an element can apply an aura, i.e., attached to entity
     */
    static bool canApplyAura(Element element);

};

#endif //AP_PROJ_ELEMENTUTIL_H
