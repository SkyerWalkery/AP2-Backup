#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    // Initialize game field
    game_field_.loadLevelFromFile("test_level");
    auto* view = new QGraphicsView();
    view->setScene(&game_field_);
    QRectF rect = game_field_.sceneRect();
    qreal margin = 64;
    rect.setWidth(rect.width() + margin);
    rect.setHeight(rect.height() + margin);
    view->setFixedSize(rect.size().toSize());

    // Set main layout
    main_layout_ = new QVBoxLayout();
    main_layout_->addWidget(view);
    auto* central_widget = new QWidget();
    central_widget->setLayout(main_layout_);
    setCentralWidget(central_widget);
    setWindowTitle("Awesome Demo");

    // Set MenuBar
    // TODO: Implement functions of menu
    auto* menu_bar = menuBar();
    QAction* file_menu = menu_bar->addAction("File");

    // Set ToolBar
    // TODO: Add buttons to tool-bar
    auto* tool_bar = new QToolBar();
    addToolBar(tool_bar);

}

void MainWindow::startGame() {
    game_field_.startGame();
}
