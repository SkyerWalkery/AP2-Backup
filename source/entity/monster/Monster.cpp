#include "Monster.h"
#include <QGraphicsLinearLayout>
#include <QPen>
#include <QLabel>

qreal Monster::MonsterSize = 0;

Monster::Monster(QGraphicsItem *parent) : Entity(parent) {
    attack_range_ = 1; // Monster's tryAttack range is 1 block by default
    can_be_attacked_ = true;
    setZValue(2);

    health_bar_ = new QGraphicsRectItem(0, 0, MonsterSize, 4, this);
    health_bar_->setPen(QPen(Qt::transparent));
    health_bar_->setBrush(QBrush(Qt::transparent));
    //updateHealthBar();

    element_aura_icon_ = new QGraphicsPixmapItem(this);
    QPixmap empty_pix(32, 32);
    element_aura_icon_->setPixmap(empty_pix);
    element_aura_icon_->setX(MonsterSize / 2 - element_aura_icon_->boundingRect().center().x());
    element_aura_icon_->setY(MonsterSize * 2 / 3);
    element_aura_icon_->setVisible(false);

    auto* buff_icons_layout = new QGraphicsLinearLayout;
    for(auto buff: BuffUtil::monsterBuffs()){
        auto icon_name = BuffUtil::buffToIcon(buff);
        auto icon_pixmap = QPixmap(icon_name).scaled(BUFF_ICON_SIZE, BUFF_ICON_SIZE);

        auto* icon = new QLabel();
        icon->setStyleSheet("background-color: rgba(0,0,0,0%)");
        icon->setPixmap(icon_pixmap);
        auto* proxy = new QGraphicsProxyWidget;
        proxy->setWidget(icon);
        buff_to_icon_[buff] = proxy;
        proxy->setVisible(false); // Buff cannot be used at very begin of game
        buff_icons_layout->addItem(proxy);
    }
    buff_icons_->setLayout(buff_icons_layout);
    buff_icons_->setY(-BUFF_ICON_SIZE - 4);
}

QColor Monster::getHealthBarColor() const {
    // Color of health bar
    // color[i] is color when health is between {i * (1/max)} and {(i+1) * (1/max)}
    static QList<QColor> HealthBarColor = {
            QColor(255, 0, 0),
            QColor(255, 128, 0),
            QColor(255, 255, 0),
            QColor(128, 255, 0),
            QColor(0, 255, 0)
    };
    // If health is at max, set health bar as invisible
    if(health_ >= max_health_)
        return Qt::transparent;
    return HealthBarColor[getHealth() * HealthBarColor.size() / getMaxHealth()];
}

void Monster::updateHealthBar() {
    // No damage taken until now, don't show health bar
    if(getHealth() == getMaxHealth())
        return;
    // Set color accordingly
    auto pen = health_bar_->pen();
    pen.setColor(Qt::white);
    auto brush = health_bar_->brush();
    brush.setColor(getHealthBarColor());
    health_bar_->setBrush(brush);
    health_bar_->setPen(pen);

    // Set length of bar
    qreal bar_len = MonsterSize * getHealth() / getMaxHealth();
    health_bar_->setRect(0, 0, bar_len, 4);
}

void Monster::updateBuffIcon() {
    bool should_change_pos = false;
    for(auto buff: BuffUtil::monsterBuffs()){
        auto* buff_icon = buff_to_icon_[buff];
        auto* icon = qobject_cast<QLabel*>(buff_icon->widget());
        if(bool has_buff = hasBuff(buff); has_buff != icon->isVisible()) {
            icon->setVisible(has_buff);
            should_change_pos = true;
        }
    }
    if(should_change_pos) {
        buff_icons_->setVisible(false);
        buff_icons_->setVisible(true); // Redraw layout
        buff_icons_->setX(this->boundingRect().center().x() - buff_icons_->boundingRect().center().x());
    }
}

void Monster::updateElementAuraIcon(){
    if(element_aura_ == Element::NONE) {
        element_aura_icon_->setVisible(false);
        return;
    }
    element_aura_icon_->setVisible(true);
    auto icon = QPixmap(ElementUtil::elementToIcon(element_aura_)).scaled(32, 32);
    element_aura_icon_->setPixmap(icon);
}

qreal Monster::getSpeed() const {
    qreal real_speed = speed_;
    // If buff exists...
    // Pay attention to sequence of if-clauses
    if(buffs_.contains(Buff::WINDFALL))
        real_speed += speed_ / 3; // Speed increases by 30%
    if(buffs_.contains(Buff::FROZEN))
        real_speed = 0; // If frozen, speed would be 0 even when having a speed increase

    return real_speed;
}

void Monster::setSpeed(qreal speed) {
    if(speed < 0.0)
        return;
    speed_ = speed;
}

Monster::Direction Monster::getDirection() const {
    return direction_;
}

void Monster::setDirection(const Monster::Direction &direction) {
    direction_ = direction;
    // Set orientation according to monster's moving direction
    if((direction_.first == -1) ^ is_horizontally_flipped_)
        flipHorizontally();
}

void Monster::setMonsterSize(qreal size) {
    MonsterSize = size;
}

void Monster::updateStatus() {
    Entity::updateStatus();
    updateHealthBar();
    updateBuffIcon();
    updateElementAuraIcon();
    rechargeSkill();
}

void Monster::rechargeSkill() {
    skill_recharged_ += GameRefreshInterval;
}

bool Monster::tryFlash(){
    if(!hasBuff(Buff::EVER_CHANGING) || skill_recharged_ < SKILL_CD)
        return false;
    skill_recharged_ %= SKILL_CD;
    return true;
}
