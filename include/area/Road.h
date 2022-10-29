#ifndef AP_PROJ_ROAD_H
#define AP_PROJ_ROAD_H

#include <QHash>
#include <QPair>
#include <QList>
#include "Area.h"

class Road: public Area{

    static constexpr const char* TEXTURE = ":/images/road.png";

    using Direction = QPair<int, int>;

    // Map from "from direction_" to "to direction_"
    // Suppose a monster come from upside (direction_{0, 1}),
    // and it should go left (direction_{-1, 0}),
    // then from2to_[{0, 1}] = {-1, 0}
    // By default, from2to_[any] = {0, 0}
    QHash<Direction, Direction> from2to_;

public:

    explicit Road(QGraphicsItem *parent = nullptr);

    // Used in qgraphicsitem_cast
    enum { Type = UserType + 2 };
    int type() const override;

    Road& setDirection(const Direction & from, const Direction& to);

    Direction getToDirection(const Direction & from) const;
};

#endif //AP_PROJ_ROAD_H
