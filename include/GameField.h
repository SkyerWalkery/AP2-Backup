#ifndef AP_PROJ_GAMEFIELD_H
#define AP_PROJ_GAMEFIELD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QStringList>
#include <QSet>
#include <QPair>
#include "Grass.h"
#include "Road.h"


class GameField: public QGraphicsScene{

    int field_length_ = 0;
    int field_width_ = 0;
    qreal area_scale_factor_ = 3.0; // scale factor of area

    QList<QList<QGraphicsPixmapItem*>> areas_;

public:
    explicit GameField(QObject* parent = nullptr);

    void loadFieldFromFile(const QString& file_path);

};

#endif //AP_PROJ_GAMEFIELD_H
