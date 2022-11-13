#ifndef AP_PROJ_BUFFUTIL_H
#define AP_PROJ_BUFFUTIL_H

#include "Buff.h"
#include <QList>


/*
 * Utility class for buff
 */
class BuffUtil{

    static constexpr const char* ICON_DAMAGE_UP = ":/icons/damage_up.png";
    static constexpr const char* ICON_MOVE_SPEED_UP = ":/icons/movement_speed_up.png";

public:

    /**
     * Returns a const QList of buffs which characters can have.
     */
    static const QList<Buff>& characterBuffs(){
        static QList<Buff> character_buffs = {
                Buff::WOLF_S_GRAVESTONE,
                Buff::CAUSE_CORROSION,
                /*
                Buff::INFUSION_PYRO,
                Buff::INFUSION_HYDRO,
                Buff::INFUSION_CYRO,
                Buff::INFUSION_ANEMO,
                 */
                Buff::INFUSION_FROZEN,
        };
        return character_buffs;
    }

    /**
     * Returns file name of icon of buff
     */
    static QString buffToIcon(Buff buff){
        switch (buff) {
            case Buff::WOLF_S_GRAVESTONE:
                return ICON_DAMAGE_UP;
            case Buff::INFUSION_FROZEN:
                return ICON_DAMAGE_UP; // TODO: Proper image to be found
            case Buff::CAUSE_CORROSION:
                return ICON_DAMAGE_UP; // TODO: Proper image to be found
            default:
                throw std::invalid_argument("No icon for buff");
        }
    }

    /**
     * Returns if the specific buff is a de-buff
     */
     static bool isDeBuff(Buff buff){
         return buff == Buff::CORRODED || buff == Buff::FROZEN;
     }
};


inline quint64 qHash(const Buff& buff){
    return qHash(static_cast<int>(buff));
}


#endif //AP_PROJ_BUFFUTIL_H
