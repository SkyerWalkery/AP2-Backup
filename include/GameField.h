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
#include "Grass.h"
#include "Road.h"
#include "Monster.h"
#include "TestMonster.h"


class GameField: public QGraphicsScene{

    static constexpr const int AREA_SIZE = 48; // px

    int num_rows_ = 0;
    int num_cols_ = 0;

    QTimer timer_;
    qreal fps_ = 60; // refresh rate

    QList<QList<QGraphicsPixmapItem*>> areas_;
    QList<TestMonster*> monsters_;

public:
    explicit GameField(QObject* parent = nullptr);

    void loadFieldFromFile(const QString& file_path);

    void setFps(qreal fps);

    void moveMonsters();
};

#endif //AP_PROJ_GAMEFIELD_H
