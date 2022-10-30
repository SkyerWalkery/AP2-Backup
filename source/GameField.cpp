#include "GameField.h"


GameField::GameField(QObject* parent):
    QGraphicsScene(parent)
{
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
    // "row_idx,col_idx,to_direction,to_direction,to_direction,to_direction,road_type"
    // The 4 directions are values mapped from {-1, 0}, {0, 1}, {1, 0}, {0, -1}
    // Each direction_ looks like "x,y", so it should be split by ',' as well
    // road_type: 1 to start, 2 to Protection Objective, otherwise 0
    // TODO: Invalid input
    line = in_file.readLine();
    int num_roads = line.toInt();
    QHash<AreaIndex, Area*> pos2road;
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
        AreaIndex pos = qMakePair(info[0].toInt(), info[1].toInt());
        pos2road[pos] = road;
        if(info[10].toInt() == 1)
            start_areas_idx_.push_back(pos);
        else if(info[10].toInt() == 2)
            protect_areas_idx_.push_back(pos);
    }
    in_file.close();

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

void GameField::loadCharacterOptionFromFile(const QString& file_path) {
    // For time, characters info are hard coded
    // TODO: Init from file

    // Construct place buttons and set as invisible
    // Need to add a background before
    auto* build_options_layout = new QGraphicsLinearLayout;
    for(int i = 0; i < 3; ++i){
        // Get icon and add a background
        QString file_name = QString(":/images/test_tower%1.png").arg(i + 1);
        auto button_pixmap = QPixmap(file_name);
        /*
         * Add a background (not needed when a default background is given by QPushButton)
        auto mask = button_pixmap.createMaskFromColor(Qt::transparent, Qt::MaskOutColor);
        auto painter = QPainter(&button_pixmap);
        painter.setPen(QColor(255, 255, 255, 128));
        painter.drawPixmap(button_pixmap.rect(), mask, mask.rect());
        painter.end();
         */
        button_pixmap = button_pixmap.scaled(CHARACTER_OPTION_SIZE, CHARACTER_OPTION_SIZE);
        auto* button = new QPushButton();
        button->setIcon(button_pixmap);
        button->setIconSize(QSize(CHARACTER_OPTION_SIZE, CHARACTER_OPTION_SIZE));
        auto* proxy = new QGraphicsProxyWidget;
        proxy->setWidget(button);
        build_options_layout->addItem(proxy);
    }
    this->place_options_->setLayout(build_options_layout);
    // Scale to a fixed size
    addItem(place_options_);
    place_options_->setVisible(false);
    place_options_->setZValue(1);

    // Initialize some info of characters,
    // including area size
    Character::setAreaSize(AREA_SIZE);
}

void GameField::setFps(qreal fps) {
    fps_ = fps;
    timer_.setInterval(static_cast<int>(1000 /* ms */ / fps_));
}


void GameField::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    if(place_options_->isVisible()) {
        place_options_->setVisible(false);
        return;
    }
    auto pos = mouseEvent->scenePos();
    auto area_idx = posToIndex(pos);
    auto* grass = qgraphicsitem_cast<Grass*>(areas_[area_idx.first][area_idx.second]);
    if(!grass) // The area is road: do nothing.
        return;
    if(grass->isOccupied()){
        // TODO: Edit the character
    }
    else{
        // TODO: need to be implemented
        // Grass is empty
        // First, show towers can be built
        // Then, (if player click) build a character
        displayBuildOptions(area_idx);
    }
}


void GameField::displayBuildOptions(AreaIndex area_idx) {
    auto* area = areas_[area_idx.first][area_idx.second];
    auto pos = area->pos();
    // Set the buttons below the area vertically
    // and in the middle of the area horizontally
    place_options_->setPos(pos.x() - place_options_->size().width() / 2 + AREA_SIZE / 2, pos.y() + AREA_SIZE);
    place_options_->setVisible(true);
}



void GameField::moveMonsters() {
    for(auto* monster: monsters_){
        qreal total_move_dis = monster->getSpeed() * timer_.interval() / 1000;
        while(total_move_dis > REAL_COMPENSATION){
            // Limit move_dis in one loop
            // so that it is not more than one area.
            // For security, the limit is half the size of area
            qreal move_dis = qMin(AREA_SIZE / 2, total_move_dis);
            total_move_dis -= move_dis;

            auto cur_direction = monster->getDirection();
            if(cur_direction == qMakePair(0, 0))
                break;
            auto cur_pos = monster->pos();
            auto next_pos = cur_pos;
            next_pos.setX(next_pos.x() + cur_direction.first * move_dis);
            next_pos.setY(next_pos.y() + cur_direction.second * move_dis);

            auto cur_area_idx = posToIndex(cur_pos);
            auto next_area_idx = posToIndex(next_pos);

            // After moving, monster is in the origin area.
            if(cur_area_idx == next_area_idx){
                monster->setPos(next_pos);
                move_dis = 0.0;
                auto cur_area = qgraphicsitem_cast<Road*>(areas_[cur_area_idx.first][cur_area_idx.second]);
                // If pos is same as any area,
                // direction may need to be changed
                if(pointFloatEqual(monster->pos(), cur_area->pos()))
                    monster->setDirection(cur_area->getToDirection(monster->getDirection()));
                break;
            }

            /* Go into another area
             *
             * In posToIndex(), each area has two edges,
             * so there are 2 situations.
             *
             * If direction is {-1, 0} or {0, -1},
             * new direction should come from next_area
             *
             * Else if direction is {1, 0} or {0, 1},
             * new direction should come from cur_area
             *
             * For more details, refer to code below
             */

            /* Note:
             * Under normal conditions, next_area would not out of range,
             * so just ignore the condition
             */

            auto cur_area = qgraphicsitem_cast<Road*>(areas_[cur_area_idx.first][cur_area_idx.second]);
            if(cur_direction == qMakePair(-1, 0)
                || cur_direction == qMakePair(0, -1)){
                auto cur_area_pos = cur_area->pos();
                move_dis -= qAbs(cur_area_pos.x() - cur_pos.x());
                move_dis -= qAbs(cur_area_pos.y() - cur_pos.y());
                // Edge condition: monster's pos is exactly the pos of area,
                // direction has been set before, and cannot be reset.
                if(!pointFloatEqual(monster->pos(), cur_area->pos()))
                    monster->setDirection(cur_area->getToDirection(monster->getDirection()));
                monster->setPos(cur_area_pos);

                // Reach protection obj
                if(protect_areas_idx_.contains(cur_area_idx)){
                    monster->setDirection(qMakePair(0, 0));
                    break;
                }

                // Attention: if new direction is same as th old one
                // and monster's pos is exactly the one of some area,
                // we need to continue moving.
                qreal cont_move_dis = qMin(AREA_SIZE / 2, move_dis);
                cur_direction = monster->getDirection();
                cur_pos = monster->pos();
                next_pos = cur_pos;
                next_pos.setX(next_pos.x() + cur_direction.first * cont_move_dis);
                next_pos.setY(next_pos.y() + cur_direction.second * cont_move_dis);
                move_dis -= cont_move_dis;
                monster->setPos(next_pos);
            }
            else{
                auto next_area = qgraphicsitem_cast<Road*>(areas_[next_area_idx.first][next_area_idx.second]);
                auto next_area_pos = next_area->pos();
                move_dis -= qAbs(next_area_pos.x() - cur_pos.x());
                move_dis -= qAbs(next_area_pos.y() - cur_pos.y());
                monster->setPos(next_area_pos);
                monster->setDirection(next_area->getToDirection(monster->getDirection()));
                // Reach protection obj
                if(protect_areas_idx_.contains(next_area_idx)){
                    monster->setDirection(qMakePair(0, 0));
                    break;
                }
            }
            // if move_dis is greater than 0, it needs to be back to total distance
            if(move_dis > REAL_COMPENSATION)
                total_move_dis += move_dis;
        }
    }
    checkReachProtectionObjective();
}

typename GameField::AreaIndex GameField::posToIndex(QPointF pos) {
    qreal x = pos.x();
    qreal y = pos.y();
    auto res = qMakePair(0, 0);
    res.second = x < 0 ? -1 : qFloor(x + REAL_COMPENSATION) / qRound(AREA_SIZE);
    res.first = y < 0 ? -1 : qFloor(y + REAL_COMPENSATION) / qRound(AREA_SIZE);
    return res;
}


bool GameField::qRealEqual(qreal r1, qreal r2) {
    return qAbs(r1 - r2) <= REAL_COMPENSATION;
}


bool GameField::pointFloatEqual(const QPointF& p1, const QPointF& p2){
    return qRealEqual(p1.x(), p2.x()) && qRealEqual(p1.y(), p2.y());
}


void GameField::debugStart() {
    for(auto& start_idx: start_areas_idx_){
        Monster* monster = new TestMonster();
        addItem(monster);
        monsters_.push_back(monster);
        auto start_area = areas_[start_idx.first][start_idx.second];
        auto start_pos = start_area->pos();
        monster->setPos(start_pos);
        qreal scale_factor = AREA_SIZE / (monster->boundingRect().height() - 1);
        monster->setScale(scale_factor);

        int directions[5] = {-1, 0, 1, 0, -1};
        for(int i = 0; i < 4; ++i){
            Direction from = qMakePair(directions[i], directions[i + 1]);
            // C++17 If statement with initializer
            if(auto to = qgraphicsitem_cast<Road*>(start_area)->getToDirection(from); to != qMakePair(0, 0)) {
                monster->setDirection(to);
                break;
            }
        }
    }
    timer_.start();
}

void GameField::checkReachProtectionObjective() {
    auto it = monsters_.begin();
    while(it != monsters_.end()){
        Monster* monster = *it;
        // Still heading for protection objective
        if(monster->getDirection() != qMakePair(0, 0)) {
            ++it;
            continue;
        }
        auto cur_pos = monster->pos();
        auto cur_area_idx = posToIndex(cur_pos);
        if(!protect_areas_idx_.contains(cur_area_idx)){
            throw std::runtime_error(
                    "Game Error: monster direction is {0, 0} "
                    "but hasn't reach protection objective"
                    );
        }
        life_points_--;
        removeItem(monster);
        it = monsters_.erase(it);
    }
    checkGameEnd();
}

void GameField::checkGameEnd() {
    if(life_points_ > 0)
        return;

    auto* background = new QGraphicsRectItem;
    background->setPen(Qt::NoPen);
    background->setBrush(QBrush(QColor(255, 0, 0, 128)));
    background->setRect(this->sceneRect());
    addItem(background);
    timer_.stop();
}

Character *GameField::typeToCharacter(CharacterType type) {
    switch(type){
        case CharacterType::ELF:
            return new Elf;
        default:
            throw std::invalid_argument("Invalid character type");
    }
}

QString *GameField::typeToCharacter(CharacterType type) {
    switch(type){
        case CharacterType::ELF:
            return new Elf;
        default:
            throw std::invalid_argument("Invalid character type");
    }
}
