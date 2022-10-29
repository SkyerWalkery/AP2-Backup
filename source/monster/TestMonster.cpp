#include "TestMonster.h"

TestMonster::TestMonster(QGraphicsItem *parent) : Monster(parent) {
    setPixmap(QPixmap(TEXTURE));
    speed_ = 240;
}
