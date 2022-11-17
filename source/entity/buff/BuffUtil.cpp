#include "BuffUtil.h"
#include <stdexcept>


const QList<Buff>& BuffUtil::characterBuffs(){
    static QList<Buff> character_buffs = {
            Buff::WOLF_S_GRAVESTONE,
            Buff::CAUSE_CORROSION,
            Buff::INFUSION_ANEMO,
            /*
            buff::INFUSION_PYRO,
            buff::INFUSION_HYDRO,
            buff::INFUSION_CRYO,
             */

            Buff::INFUSION_FROZEN,
    };
    return character_buffs;
}

QString BuffUtil::buffToIcon(Buff buff){
    switch (buff) {
        case Buff::WOLF_S_GRAVESTONE:
            return ICON_DAMAGE_UP;
        case Buff::INFUSION_FROZEN:
            return ICON_FROZEN;
        case Buff::INFUSION_ANEMO:
            return ICON_ANEMO;
        case Buff::CAUSE_CORROSION:
            return ICON_CORROSION;
        default:
            throw std::invalid_argument("No icon for buff");
    }
}

Buff BuffUtil::stringToBuff(const QString& str){
    auto upper_str = str.toUpper();
    if(upper_str == "WINDFALL")
        return Buff::WINDFALL;
    else if(upper_str == "EVER_CHANGING")
        return Buff::EVER_CHANGING;
    else
        throw std::invalid_argument("No matching buff for given string");
}

QString BuffUtil::buffToString(Buff buff){
    switch (buff) {
        case Buff::FROZEN:
            return "Frozen";
        case Buff::CORRODED:
            return "Corrode";
        default:
            throw std::invalid_argument("No matching string for buff");
    }
}

QColor BuffUtil::buffToColor(Buff buff){
    switch (buff) {
        case Buff::FROZEN:
            return {142, 255, 247};
        case Buff::CORRODED:
            return {254, 139, 139};
        default:
            throw std::invalid_argument("No matching string for buff");
    }
}

bool BuffUtil::isDeBuff(Buff buff){
    return buff == Buff::CORRODED || buff == Buff::FROZEN;
}

