#ifndef AP_PROJ_GAMEFIELD_H
#define AP_PROJ_GAMEFIELD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QStringList>
#include <QSet>
#include <QHash>
#include <QPair>
#include <QTimer>
#include <QtMath>
#include <QtGlobal>
#include "Grass.h"
#include "Road.h"
#include "Monster.h"
#include "TestMonster.h"


class GameField: public QGraphicsScene{

    using Direction = QPair<int, int>;
    using AreaIndex = QPair<int, int>;

    static constexpr const qreal AREA_SIZE = 48; // px

    int num_rows_ = 0;
    int num_cols_ = 0;

    QTimer timer_;
    qreal fps_ = 59; // refresh rate

    QList<QList<QGraphicsPixmapItem*>> areas_;
    QList<Monster*> monsters_;

    QList<AreaIndex> start_areas_idx_;
    QList<AreaIndex> terminal_areas_idx_;

public:
    explicit GameField(QObject* parent = nullptr);

    void loadFieldFromFile(const QString& file_path);

    void setFps(qreal fps);

    void moveMonsters();

    /*
    * Returns {row_idx, col_idx} of the area which pos is at.
    * If pos is out of rect of scene, a valid pair will still be returned.
    * -1 <= row_idx <= num_rows, -1 <= col_idx <= num_cols.
    */
    static AreaIndex posToIndex(QPointF pos);

    void debugStart();
};

#endif //AP_PROJ_GAMEFIELD_H
