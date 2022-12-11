#include "BuffUtil.h"
#include <stdexcept>


const QList<Buff>& BuffUtil::characterBuffs(){
    static QList<Buff> character_buffs = {
            Buff::WOLF_S_GRAVESTONE,
            Buff::CAUSE_CORROSION,
            Buff::INFUSION_FROZEN,
            Buff::INFUSION_ANEMO,
            Buff::INFUSION_PYRO,
            Buff::INFUSION_HYDRO,
            Buff::INFUSION_CRYO,
    };
    return character_buffs;
}

const QList<Buff>& BuffUtil::monsterBuffs() {
    static QList<Buff> monster_buffs = {
            Buff::CORRODED,
            Buff::FROZEN,
            Buff::WINDFALL,
            Buff::EVER_CHANGING,
    };
    return monster_buffs;
}

QString BuffUtil::buffToIcon(Buff buff){
    switch (buff) {
        case Buff::WOLF_S_GRAVESTONE:
            return ICON_DAMAGE_UP;
        case Buff::CAUSE_CORROSION:
        case Buff::CORRODED:
            return ICON_CORROSION;
        case Buff::WINDFALL:
            return ICON_MOVE_SPEED_UP;
        case Buff::EVER_CHANGING:
            return ICON_MOVE_SPEED_DOWN;
        case Buff::INFUSION_FROZEN:
        case Buff::FROZEN:
            return ICON_FROZEN;
        case Buff::INFUSION_ANEMO:
            return ICON_ANEMO;
        case Buff::INFUSION_PYRO:
            return ICON_PYRO;
        case Buff::INFUSION_HYDRO:
            return ICON_HYDRO;
        case Buff::INFUSION_CRYO:
            return ICON_CRYO;
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

bool BuffUtil::isInfusionBuff(Buff buff) {
    return buff == Buff::INFUSION_ANEMO
        || buff == Buff::INFUSION_CRYO
        || buff == Buff::INFUSION_HYDRO
        || buff == Buff::INFUSION_PYRO;
}

