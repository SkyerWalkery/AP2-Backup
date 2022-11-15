#ifndef AP_PROJ_SIMPLETEXTPARTICLE_H
#define AP_PROJ_SIMPLETEXTPARTICLE_H

#include <QGraphicsSimpleTextItem>
#include <QColor>

/**
 * Visual effect of simple text
 * The animation an be divided into 2 phases
 * P1: Text appears and then becomes bigger
 * P2: Text's size is fixed and text becomes transparent
 *
 * @inherit QObject, QGraphicsSimpleTextItem
 */

class SimpleTextParticle: public QObject, public QGraphicsSimpleTextItem{
    Q_OBJECT
    Q_PROPERTY(qreal opacity_ READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal scale_ READ scale WRITE setScale)

public:

    explicit SimpleTextParticle(const QString &text, QGraphicsItem *parent = nullptr);

    enum { Type = UserType + 1003 };
    int type() const override;

    void setTextColor(QColor color);

    void startAnimation();
};

#endif //AP_PROJ_SIMPLETEXTPARTICLE_H
