#ifndef AP_PROJ_GAMEFIELD_H
#define AP_PROJ_GAMEFIELD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QSet>
#include <QHash>
#include <QPair>
#include <QPoint>
#include <QTimer>
#include <QtMath>
#include <QtGlobal>
#include <QRandomGenerator>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QGraphicsWidget>
#include <QTransform>
#include <QSizePolicy>
#include <QQueue>
#include <functional>
#include "Grass.h"
#include "Road.h"
#include "Monster.h"
#include "Boar.h"
#include "Character.h"
#include "Elf.h"
#include "Knight.h"


class GameField: public QGraphicsScene{

    using Direction = QPair<int, int>;
    using AreaIndex = QPoint;

    static constexpr const char* UP_ICON = ":/icons/chevrons_up.svg";
    static constexpr const char* X_ICON = ":/icons/x_square.svg";

    static constexpr const qreal AREA_SIZE = 48; // px
    static constexpr const qreal CHARACTER_OPTION_SIZE = 32; // px
    static constexpr const qreal CHARACTER_SIZE = 48; // px
    static constexpr const qreal MONSTER_SIZE = 48; // px
    static constexpr const qreal REAL_COMPENSATION = 0.0000001;

    int num_rows_ = 0;
    int num_cols_ = 0;

    QTimer timer_;
    qint64 game_time_ = 0; // time (ms) since game start; It should be updated by updateField
    qreal fps_ = 59; // refresh rate

    // Queue of (monster, arrival time) pairs
    // time (second of pair) should be sorted by ascending order
    QQueue<QPair<Monster*, int>> monster_que_;

    QList<QList<Area*>> areas_;
    QList<Monster*> monsters_;
    QList<Character*> characters_;

    QList<AreaIndex> start_areas_idx_;
    QList<AreaIndex> protect_areas_idx_;

    int life_points_ = 1;

    // Below are components related to character.
    // place_options_ and upgrade_options_ each holds a layout, which may holds more than one options
    // place_options_ is used to place characters
    // upgrade_options_ is used to upgrade or remove characters
    QGraphicsWidget* place_options_ = new QGraphicsWidget;
    QGraphicsWidget* upgrade_options_ = new QGraphicsWidget;
    // character_makers_ contains makers of characters that can be placed in this field
    // character_textures_ is list of file name of corresponding textures
    QList<std::function<Character*()>> character_makers_;
    QStringList character_textures_;

public:
    explicit GameField(QObject* parent = nullptr);

    /*
     * Load data from files
     * dir_path should contain 3 files:
     * field.dat: data of field
     * characters.dat: characters can be used
     * monsters.dat: monsters that will appear in this level, along with time of arrival
     * @param dir_path const QString& directory having data of field, monsters and characters cna be used
     */
    void loadLevelFromFile(const QString& dir_path);

    void loadFieldFromFile(const QString& file_path);

    void loadCharacterOptionFromFile(const QString& file_path);

    void loadMonsterQueueFromFile(const QString& file_path);

    void loadLevelSettingFromFile(const QString& file_path);

    // Initialize place_options_ and upgrade_options_
    // Must be called explicitly, for no other functions will call it
    void initOptionUi();

    void setFps(qreal fps);

    // Start the game
    // Should be called explicitly
    void startGame();

private:

    /*
     * Called by updateField()
     * Move monsters in each frame
     */
    void moveMonsters();

    /*
     * Called by updateField()
     * Check if monsters are to be generated in each frame.
     * If so, do it.
     */
    void generateMonsters();

    /*
     * Called by updateField()
     * Check monsters and characters, handle interactions between them
     * e.g. An Elf attack a Boar, a Boar attacks a Knight
     */
    void entityInteract();

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void displayCharacterOptions(const AreaIndex& area_idx, QGraphicsWidget* options);

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
     * Return distance between p1 and p2
     */
    static qreal distanceBetween(const QPointF& p1, const QPointF& p2);

    /*
     * Check if any monster has reached the Protection Objective.
     * If so, remove it from the field and minus life_points_ by 1.
     * If
     */
    void checkReachProtectionObjective();


    void checkGameEnd();

private slots:

    /*
     * Slot for game timer
     * It should do all things controlled by game timer,
     * e.g. move monsters, make attack actions
     * In order to ensure they're called in fixed order, we have this slot
     * For more, please refer to implementation
     */
    void updateField();

    /*
     * Slot for placeCharacter button
     * Note: need a lambda to pass parameter `type`
     * @param type: type of character (call typeToCharacter() to make a new character)
     */
    void placeCharacter(const std::function<Character*()>& maker);

    /*
     * Slot for upgradeCharacter button
     */
    void upgradeCharacter();

    /*
     * Slot for removeCharacter button
     */
    void removeCharacter();

};

#endif //AP_PROJ_GAMEFIELD_H
