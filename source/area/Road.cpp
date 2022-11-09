#include "Road.h"
#include <QHash>
#include <QList>



Road::Road(QGraphicsItem *parent) : Area(parent) {
    int sz = static_cast<int>(AreaSize);
    if(sz <= 0)
        throw std::invalid_argument("Area Size not initialized");
    setPixmap(QPixmap(TEXTURE).scaled(sz, sz));

    // Initialize from2to_ table
    int directions[5] = {-1, 0, 1, 0, -1};
    for(int i = 0; i < 4; ++i)
        from2to_[qMakePair(directions[i], directions[i + 1])] = qMakePair(0, 0);
}

int Road::type() const {
    return Type;
}

Road &Road::setDirection(const Direction &from, const Direction &to) {
    int directions[5] = {-1, 0, 1, 0, -1};
    for(int i = 0; i < 4; ++i) {
        Direction curr_from = qMakePair(directions[i], directions[i + 1]);
        if(curr_from == from) {
            from2to_[curr_from] = to;
            return *this;
        }
    }
    throw std::invalid_argument("Invalid key");
}

Road::Direction Road::getToDirection(const Direction & from) const {
    return from2to_[from];
}
