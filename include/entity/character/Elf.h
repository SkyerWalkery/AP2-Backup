#ifndef AP_PROJ_ELF_H
#define AP_PROJ_ELF_H

#include "Character.h"
#include "ShootParticle.h"


class Elf: public Character{

public:

    static constexpr const char* VOICES[] = {
            "qrc:/sounds/HuTao_1.mp3",
            "qrc:/sounds/HuTao_2.mp3",
            "qrc:/sounds/HuTao_3.mp3",
            "qrc:/sounds/HuTao_4.mp3",
            "qrc:/sounds/HuTao_5.mp3",
    };

    static constexpr const char* TEXTURE = ":/images/elf.png";

    static constexpr const int AreaCond = Character::ON_GRASS;

    static constexpr const int SunCost = 0; // Cost to put this character

    explicit Elf(QGraphicsItem *parent = nullptr);

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 201 };
    int type() const override;

    bool testAreaCond(int cond) override;

    void attack(ActionAttack& action, const QList<Entity*>& candidate_targets) override;

    QString getRandomVoice() const override;
};


#endif //AP_PROJ_ELF_H
