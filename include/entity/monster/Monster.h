#ifndef AP_PROJ_MONSTER_H
#define AP_PROJ_MONSTER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsWidget>
#include <QGraphicsProxyWidget>
#include <QPair>
#include "Entity.h"


class Monster: public Entity{

    using Direction = QPair<int, int>;

    static constexpr const qreal BUFF_ICON_SIZE = 16; // px

protected:

    Direction direction_ = qMakePair(0, 0);
    qreal speed_ = 10.0; // num of px per second to move

    QGraphicsRectItem* health_bar_;
    QGraphicsPixmapItem* element_aura_icon_;

    static qreal MonsterSize; // Must be set before construct

    // CD (ms) for skill, e.g. flash (when having "EVER-CHANGING" buff)
    static constexpr const int SKILL_CD = 10 * 1000;

    // Recharged val (ms) for using skill
    // Should be updated in rechargeSkill() and when using a skill
    int skill_recharged_ = 0;

    // buff_icons_ holds a layout, which contains multiple buffs(QLable) attached to monster.
    QGraphicsWidget* buff_icons_ = new QGraphicsWidget(this);
    // You can use buff to control corresponding icon
    QHash<Buff, QGraphicsProxyWidget*> buff_to_icon_;

    QColor getHealthBarColor() const;

    void updateHealthBar();

    void updateElementAuraIcon();

    void updateBuffIcon();

    void rechargeSkill();

public:

    explicit Monster(QGraphicsItem *parent = nullptr);

    qreal getSpeed() const;

    void setSpeed(qreal speed);

    Direction getDirection() const;

    void setDirection(const Direction& direction);

    /**
     * Try to make a flash when blocked (this condition is met by default, you should check it in GameField::moveMonsters())
     * @returns false if not having Buff::EVER_CHANGING or not recharged, true otherwise
     */
    bool tryFlash();

    static void setMonsterSize(qreal size);

    void updateStatus() override;

};

#endif //AP_PROJ_MONSTER_H
