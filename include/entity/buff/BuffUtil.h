#ifndef AP_PROJ_BUFFUTIL_H
#define AP_PROJ_BUFFUTIL_H

#include "Buff.h"
#include <QList>


/**
 * Utility class for buff
 */
class BuffUtil{

    static constexpr const char* ICON_DAMAGE_UP = ":/icons/damage_up.png";
    static constexpr const char* ICON_MOVE_SPEED_UP = ":/icons/movement_speed_up.png";
    static constexpr const char* ICON_CORROSION = ":/icons/corrosion.png";
    static constexpr const char* ICON_FROZEN = ":/icons/element_cryo.png";

public:

    /**
     * Returns a const QList of buffs which characters can have.
     */
    static const QList<Buff>& characterBuffs();

    /**
     * Returns file name of icon of buff
     */
    static QString buffToIcon(Buff buff);

    /**
     * Returns buff that given string indicated.
     * Exception will be thrown if invalid string is given
     */
     static Buff stringToBuff(const QString& str);

    /**
     * Returns if the specific buff is a de-buff
     */
     static bool isDeBuff(Buff buff);
};


inline quint64 qHash(const Buff& buff){
    return qHash(static_cast<int>(buff));
}


#endif //AP_PROJ_BUFFUTIL_H
