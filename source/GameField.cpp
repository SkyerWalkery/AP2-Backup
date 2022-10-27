#include "GameField.h"


GameField::GameField(QObject* parent): QGraphicsScene(parent) {
    // handle process events
    timer_.setInterval(static_cast<int>(1000 /* ms */ / fps_));
    connect(&timer_, &QTimer::timeout, this, &GameField::moveMonsters);
}

void GameField::loadFieldFromFile(const QString &file_path) {
    QFile in_file(file_path);
    if(!in_file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QString line;
    // read length and width
    line = in_file.readLine();
    QStringList size = line.split(u',', Qt::SkipEmptyParts);
    num_rows_ = size[0].toInt();
    num_cols_ = size[1].toInt();
    if(num_rows_ <= 0 || num_cols_ <= 0)
        throw std::invalid_argument("Invalid field size");

    // read indices of road areas
    // begin with a line, with size of roads in it
    // then comes size lines, each of them looks like this:
    // "row_idx,col_idx,to_direction,to_direction,to_direction,to_direction"
    // The 4 directions are values mapped from {-1, 0}, {0, 1}, {1, 0}, {0, -1}
    // Each direction looks like "x,y", so it should be split by ',' as well
    // TODO: Invalid input
    line = in_file.readLine();
    int num_roads = line.toInt();
    QHash<QPair<int, int>, Area*> pos2road;
    for(int i = 0; i < num_roads; ++i){
        line = in_file.readLine();
        QStringList info = line.split(u',', Qt::SkipEmptyParts);
        Road* road = new Road();
        int directions[5] = {-1, 0, 1, 0, -1};
        for(int k = 0; k < 4; ++k){
            QPair<int, int> from = qMakePair(directions[k], directions[k + 1]);
            QPair<int, int> to = qMakePair(info[2 + k * 2].toInt(), info[3 + k * 2].toInt());
            road->setDirection(from, to);
        }
        QPair<int, int> pos = qMakePair(info[0].toInt(), info[1].toInt());
        pos2road[pos] = road;
    }

    // fill the field
    areas_ = QList<QList<QGraphicsPixmapItem*>>(num_cols_);
    for(int i = 0; i < num_cols_; ++i){
        for(int j = 0; j < num_rows_; ++j){
            auto pos = qMakePair(i, j);
            QGraphicsPixmapItem* item = pos2road.value(pos, new Grass());
            addItem(item);
            // scale to 48 px
            // height should minus 1
            qreal area_scale_factor = AREA_SIZE / (item->boundingRect().height() - 1);
            item->setPos(AREA_SIZE * j, AREA_SIZE * i);
            item->setScale(area_scale_factor);
            areas_[i].push_back(item);
        }
    }
}

void GameField::setFps(qreal fps) {
    fps_ = fps;
    timer_.setInterval(static_cast<int>(1000 /* ms */ / fps_));
}

void GameField::moveMonsters() {
    for(auto* monster: monsters_){
        qreal move_dis = monster->getSpeed() * timer_.interval() / 1000;
        while(move_dis > 0.0){
            // TODO: HOW TO MOVE
        }
    }
}

