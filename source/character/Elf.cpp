#include "Elf.h"

Elf::Elf(QGraphicsItem *parent) :Character(parent){
    setPixmap(QPixmap(TEXTURE));
    damage_ = 1;
    recharge_time_ = 700; // ms
    attack_range_ = 5;
}

int Elf::type() const {
    return Type;
}

bool Elf::testAreaCond(int cond) {
    return cond & AreaCond;
}
