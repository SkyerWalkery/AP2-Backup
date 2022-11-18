#include "MainWindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    // Initialize game field
    game_field_ = new GameField();
    game_field_->loadLevelFromFile(level_data_path_);
    game_view_ = new QGraphicsView();
    game_view_->setScene(game_field_);
    game_view_->setSceneRect(game_field_->sceneRect());

    // Set main layout
    main_layout_ = new QVBoxLayout();
    main_layout_->addWidget(game_view_);
    auto* central_widget = new QWidget();
    central_widget->setLayout(main_layout_);
    setCentralWidget(central_widget);
    setWindowTitle("Awesome Demo");

    auto* reset_game_act = new QAction(QIcon(":/icons/refresh.svg"), "Reset");
    connect(reset_game_act, &QAction::triggered, this, &MainWindow::resetGame);
    auto* load_level_act = new QAction(QIcon(":/icons/plus.svg"), "New Level");
    connect(reset_game_act, &QAction::triggered, this, &MainWindow::loadLevel);
    auto* pause_game_act = new QAction(QIcon(":/icons/pause.svg"), "Pause");
    pause_game_act->setCheckable(true);
    connect(pause_game_act, &QAction::toggled, this, &MainWindow::pauseOrResumeGame);

    // Set MenuBar
    auto* menu_bar = menuBar();
    QMenu* file_menu = menu_bar->addMenu("&File");
    file_menu->addAction(load_level_act);
    QMenu* game_setting_menu = menu_bar->addMenu("&Game");
    game_setting_menu->addAction(reset_game_act);

    // Set ToolBar
    // TODO: Add buttons to tool-bar
    auto* tool_bar = new QToolBar();
    addToolBar(tool_bar);
    tool_bar->addAction(reset_game_act);
    tool_bar->addAction(load_level_act);
    tool_bar->addSeparator();
    tool_bar->addAction(pause_game_act);

}

void MainWindow::startGame() {
    game_field_->startGame();
}

void MainWindow::resetGame() {
    delete game_field_;
    game_field_ = new GameField();
    game_field_->loadLevelFromFile(level_data_path_);
    game_view_->setScene(game_field_);

    startGame();
}

void MainWindow::pauseOrResumeGame(bool is_pause) {
    auto* pause_action = qobject_cast<QAction*>(sender());
    if(is_pause){
        game_field_->pauseGame();
        pause_action->setIcon(QIcon(":/icons/play.svg"));
        pause_action->setText("Resume");
    }
    else{
        game_field_->startGame();
        pause_action->setIcon(QIcon(":/icons/pause.svg"));
        pause_action->setText("Pause");
    }
}

void MainWindow::loadLevel() {
    // TODO: To be implemented
}
