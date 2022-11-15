#include "SimpleTextParticle.h"
#include <QFontDatabase>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QPen>

SimpleTextParticle::SimpleTextParticle(const QString &text, QGraphicsItem *parent):
    QGraphicsSimpleTextItem(text, parent)
{
    QFont font(tr("汉仪文黑-85W"), 10);
    setFont(font);
    setPen(Qt::NoPen);
}

int SimpleTextParticle::type() const {
    return Type;
}

void SimpleTextParticle::setTextColor(QColor color){
    QBrush brush(color);
    setBrush(brush);
}

void SimpleTextParticle::startAnimation() {
    auto *group = new QSequentialAnimationGroup(this);

    // Phase 1: Scale text
    auto *scale_animation = new QPropertyAnimation(this, "scale_");
    scale_animation->setDuration(500);
    scale_animation->setStartValue(1.0);
    scale_animation->setEndValue(1.5);
    scale_animation->setEasingCurve(QEasingCurve::OutCubic);
    group->addAnimation(scale_animation);

    // Phase 2: Text fades
    auto *fadeAnimation = new QPropertyAnimation(this, "opacity_");
    fadeAnimation->setDuration(600);
    fadeAnimation->setStartValue(1);
    fadeAnimation->setEndValue(0);
    fadeAnimation->setEasingCurve(QEasingCurve::OutQuart);
    group->addAnimation(fadeAnimation);

    connect(group, &QSequentialAnimationGroup::finished,
            this, &SimpleTextParticle::deleteLater);
    group->start(QAbstractAnimation::DeleteWhenStopped);
}
