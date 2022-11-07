#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    // Initialize game field
    game_field_ = new GameField();
    game_field_->loadLevelFromFile("test_level");
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

    // Set MenuBar
    // TODO: Implement functions of menu
    auto* menu_bar = menuBar();
    QMenu* file_menu = menu_bar->addMenu("&File");
    QMenu* game_setting_menu = menu_bar->addMenu("&Game");
    game_setting_menu->addAction(reset_game_act);

    // Set ToolBar
    // TODO: Add buttons to tool-bar
    auto* tool_bar = new QToolBar();
    addToolBar(tool_bar);

}

void MainWindow::startGame() {
    game_field_->startGame();
}

void MainWindow::resetGame() {
    delete game_field_;
    game_field_ = new GameField();
    game_field_->loadLevelFromFile("test_level");
    game_view_->setScene(game_field_);

    startGame();
}
