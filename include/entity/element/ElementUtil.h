#ifndef AP_PROJ_ELEMENTUTIL_H
#define AP_PROJ_ELEMENTUTIL_H

#include "Element.h"
#include "Buff.h"
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

};

#endif //AP_PROJ_ELEMENTUTIL_H
