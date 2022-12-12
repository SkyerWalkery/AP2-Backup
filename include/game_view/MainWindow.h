#ifndef AP_PROJ_MAINWINDOW_H
#define AP_PROJ_MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVBoxLayout>
#include "GameField.h"


class MainWindow: public QMainWindow{

    // UI components related to Game Field
    QLayout* main_layout_;
    GameField* game_field_;
    QGraphicsView* game_view_;

    // Directory path of level information
    QString level_data_path_;

public:

    explicit MainWindow(QWidget *parent = nullptr);

    void startGame();

    bool openLevelDir();

private slots:

    void resetGame();

    void pauseOrResumeGame(bool is_pause);

    /**
     * Load a new level from a directory during playing.
     * Should call openLevelDir() and resetGame()
     */
    void loadLevelDuringGame();

    void setFps(int fps);

};


#endif //AP_PROJ_MAINWINDOW_H
