#ifndef AP_PROJ_ELEMENTUTIL_H
#define AP_PROJ_ELEMENTUTIL_H

#include "Element.h"
#include "Buff.h"
#include "ActionAttack.h"
#include <QColor>

/**
 * Utility for element system
 */
class ElementUtil{
public:

    /**
     * Returns particle color when infused with given color
     */
    static QColor ElementToParticleColor(Element element);

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
     */
    static void makeElementReaction(Element aura, ActionAttack& action);

};

#endif //AP_PROJ_ELEMENTUTIL_H
