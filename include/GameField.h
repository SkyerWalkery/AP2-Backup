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

    static constexpr const int AREA_SIZE = 48; // px

    int num_rows_ = 0;
    int num_cols_ = 0;

    QList<QList<QGraphicsPixmapItem*>> areas_;

public:
    explicit GameField(QObject* parent = nullptr);

    void loadFieldFromFile(const QString& file_path);

};

#endif //AP_PROJ_GAMEFIELD_H
