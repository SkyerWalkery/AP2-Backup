#ifndef AP_PROJ_MAINWINDOW_H
#define AP_PROJ_MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include "GameField.h"


class MainWindow: public QMainWindow{

    QLayout* main_layout_;
    GameField game_field_;
    QGraphicsView game_view_;

public:

    explicit MainWindow(QWidget *parent = nullptr);

    void startGame();
};


#endif //AP_PROJ_MAINWINDOW_H
