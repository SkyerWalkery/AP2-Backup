#include <QApplication>
#include <QLabel>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto main_window = MainWindow();
    main_window.startGame();
    main_window.show();
    return app.exec();
}
