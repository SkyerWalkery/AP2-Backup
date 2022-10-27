#include "GameField.h"


GameField::GameField(QObject* parent): QGraphicsScene(parent) {

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
    line = in_file.readLine();
    QStringList roads = line.split(u',', Qt::SkipEmptyParts);
    QSet<QPair<int, int>> road_pos;
    for(int i = 0; i < static_cast<int>(roads.size()) - 1; i += 2){
        road_pos.insert(qMakePair(roads[i].toInt(), roads[i + 1].toInt()));
    }

    // fill the field
    areas_ = QList<QList<QGraphicsPixmapItem*>>(num_cols_);
    for(int i = 0; i < num_cols_; ++i){
        for(int j = 0; j < num_rows_; ++j){
            QGraphicsPixmapItem* item = nullptr;
            auto pos = qMakePair(i, j);
            if(road_pos.contains(pos))
                item = new Road();
            else
                item = new Grass();
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

