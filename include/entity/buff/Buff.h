#ifndef AP_PROJ_BUFF_H
#define AP_PROJ_BUFF_H

#include <QHash>

/*
 * Enum of buff
 */
enum class Buff{
    // Temporarily increases atk damage and atk speed by a set percentage (30%)
    // Name from weapon Wolf's Gravestone in genshin impact
    WOLF_S_GRAVESTONE = 1,

    // Entity corroded will lose health per second
    CAUSE_CORROSION,
    CORRODED,

    // Entity cannot move or attack temporarily
    FROZEN,

    // Temporarily increases move speed by a set percentage (30%) (only for movable entities)
    // Name from weapon Favonius Sword in genshin impact
    WINDFALL, // TODO: To be implemented

    // Entity can flash a distance
    // Name from weapon Wine and Song in genshin impact
    EVER_CHANGING,

    /*
     * Below buffs are related to Elemental Infusion.
     * If infused with element X, it would make an attack with X infused
     * Also got names from genshin impact
     */
    INFUSION_PYRO = 1001,
    INFUSION_HYDRO,
    INFUSION_CYRO,
    INFUSION_ANEMO,
    INFUSION_FROZEN,
};


#endif //AP_PROJ_BUFF_H
