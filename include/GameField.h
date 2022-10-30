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
#include <QPainter>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsWidget>
#include <QTransform>
#include <QSizePolicy>
#include "Grass.h"
#include "Road.h"
#include "Monster.h"
#include "TestMonster.h"
#include "Character.h"
#include "Elf.h"
#include "CharacterType.h"


class GameField: public QGraphicsScene{

    using Direction = QPair<int, int>;
    using AreaIndex = QPair<int, int>;

    static constexpr const qreal AREA_SIZE = 48; // px
    static constexpr const qreal CHARACTER_OPTION_SIZE = 32; // px
    static constexpr const qreal REAL_COMPENSATION = 0.0000001;

    int num_rows_ = 0;
    int num_cols_ = 0;

    QTimer timer_;
    qreal fps_ = 59; // refresh rate

    QList<QList<QGraphicsPixmapItem*>> areas_;
    QList<Monster*> monsters_;

    QList<AreaIndex> start_areas_idx_;
    QList<AreaIndex> protect_areas_idx_;

    int life_points_ = 1; // TODO: Init from file

    // Below are components related to character.
    // place_options_ holds a layout, which may holds more than one options
    QGraphicsWidget* place_options_ = new QGraphicsWidget;
    // character_types_ contains character types that can be placed in this field
    // TODO: Init from file
    QList<CharacterType> character_types_;

public:
    explicit GameField(QObject* parent = nullptr);

    void loadFieldFromFile(const QString& file_path);

    void loadCharacterOptionFromFile(const QString& file_path);

    void setFps(qreal fps);

    void debugStart();

private:

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void displayBuildOptions(AreaIndex area_idx);

    /*
    * Returns {row_idx, col_idx} of the area which pos is at.
    * If pos is out of rect of scene, a valid pair will still be returned.
    * -1 <= row_idx <= num_rows, -1 <= col_idx <= num_cols.
    */
    static AreaIndex posToIndex(QPointF pos);

    /*
     * Return if r1 equals to r2
     * Taking double precision into account
     */
    static bool qRealEqual(qreal r1, qreal r2);

    /*
     * Return if pos1 equals to pos2
     * Taking double precision into account
     * Note: qRealEqual(qreal, qreal) is called in this method
     */
    static bool pointFloatEqual(const QPointF& p1, const QPointF& p2);

    /*
     * Check if any monster has reached the Protection Objective.
     * If so, remove it from the field and minus life_points_ by 1.
     * If
     */
    void checkReachProtectionObjective();

    void checkGameEnd();

    /*
     * Map from type to pointer to a new Character
     * If type is invalid, an exception will be thrown
     */
    static Character* typeToCharacter(CharacterType type);

    /*
     * Map from type to path of texture
     * If type is invalid, an exception will be thrown
     */
    static QString typeToTexture(CharacterType type);

private slots:
    void moveMonsters();



};

#endif //AP_PROJ_GAMEFIELD_H
