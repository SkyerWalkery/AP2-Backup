#ifndef AP_PROJ_ELF_H
#define AP_PROJ_ELF_H

#include "Character.h"


class Elf: public Character{

public:

    static constexpr const char* TEXTURE = ":/images/elf.png";

    static constexpr const int SunCost = 0; // Cost to put this character

    explicit Elf(QGraphicsItem *parent = nullptr);

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 201 };
    int type() const override;


};


#endif //AP_PROJ_ELF_H
