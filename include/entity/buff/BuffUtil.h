#ifndef AP_PROJ_BUFFUTIL_H
#define AP_PROJ_BUFFUTIL_H

#include "Buff.h"
#include <QList>
#include <QColor>


/**
 * Utility class for buff
 */
class BuffUtil{

    static constexpr const char* ICON_DAMAGE_UP = ":/icons/damage_up.png";
    static constexpr const char* ICON_MOVE_SPEED_UP = ":/icons/movement_speed_up.png";
    static constexpr const char* ICON_MOVE_SPEED_DOWN = ":/icons/movement_speed_down.png";
    static constexpr const char* ICON_CORROSION = ":/icons/corrosion.png";
    static constexpr const char* ICON_FROZEN = ":/icons/element_cryo.png";
    static constexpr const char* ICON_ANEMO = ":/icons/element_anemo.png";
    static constexpr const char* ICON_PYRO = ":/icons/element_pyro.png";
    static constexpr const char* ICON_HYDRO = ":/icons/element_hydro.png";
    static constexpr const char* ICON_CRYO = ":/icons/element_cryo.png";

public:

    /**
     * Returns a const QList of buffs which characters can have.
     */
    static const QList<Buff>& characterBuffs();

    /**
     * Returns a const QList of buffs which monsters can have.
     */
    static const QList<Buff>& monsterBuffs();

    /**
     * Returns file name of icon of buff
     */
    static QString buffToIcon(Buff buff);

    /**
     * Returns buff that given string indicated.
     * Exception will be thrown if invalid string is given.
     * Used in monster data file loading
     *
     * @param str buff's name in file, which is case-insensitive
     */
     static Buff stringToBuff(const QString& str);

     /**
      * Returns string that represents given buff.
      * Exception will be thrown if invalid buff is given, i.e. no string is set for this buff.
      * Used in display effect when an attack leads to buff
      */
     static QString buffToString(Buff buff);

    /**
     * Returns color that represents given buff.
     * Exception will be thrown if invalid buff is given, i.e. no color is set for this buff.
     * Used in display effect when an attack leads to buff
     */
    static QColor buffToColor(Buff buff);

    /**
     * Returns if the given buff is a de-buff
     */
     static bool isDeBuff(Buff buff);

     /**
      * Returns if the given buff is an infusion buff.
      * An infusion buff is one that converts normal attacks to elemental damage
      */
      static bool isInfusionBuff(Buff buff);
};


inline quint64 qHash(const Buff& buff){
    return qHash(static_cast<int>(buff));
}


#endif //AP_PROJ_BUFFUTIL_H
