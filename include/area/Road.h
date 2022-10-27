#ifndef AP_PROJ_ROAD_H
#define AP_PROJ_ROAD_H

#include "Area.h"

class Road: public Area{

    static const QString TEXTURE;

public:
    explicit Road(QGraphicsItem *parent = nullptr);
};

#endif //AP_PROJ_ROAD_H
