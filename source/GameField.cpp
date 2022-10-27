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
    field_length_ = size[0].toInt();
    field_width_ = size[1].toInt();
    if(field_length_ <= 0 || field_width_ <= 0)
        throw std::invalid_argument("Invalid field size");

    // read indices of road areas
    line = in_file.readLine();
    QStringList roads = line.split(u',', Qt::SkipEmptyParts);
    QSet<QPair<int, int>> road_pos;
    for(int i = 0; i < static_cast<int>(roads.size()) - 1; i += 2){
        road_pos.insert(qMakePair(roads[i].toInt(), roads[i + 1].toInt()));
    }

    // fill the field
    areas_ = QList<QList<QGraphicsPixmapItem*>>(field_width_);
    for(int i = 0; i < field_width_; ++i){
        for(int j = 0; j < field_length_; ++j){
            QGraphicsPixmapItem* item = nullptr;
            auto pos = qMakePair(i, j);
            if(road_pos.contains(pos))
                item = new Road();
            else
                item = new Grass();
            addItem(item);
            item->setPos(16 * j * area_scale_factor_, 16 * i * area_scale_factor_);
            item->setScale(area_scale_factor_);
            areas_[i].push_back(item);
        }
    }
}

