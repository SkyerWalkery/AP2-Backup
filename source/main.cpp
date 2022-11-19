#include <QApplication>
#include <QFontDatabase>
#include <QLabel>
#include "MainWindow.h"

int main(int argc, char *argv[]) try{
    QApplication app(argc, argv);
    // Add font 'HYWenHei-85W'
    QFontDatabase::addApplicationFont(":/font/HYWenHei-85W-zh-cn.ttf");
    auto main_window = MainWindow();
    main_window.openLevelDir();
    main_window.startGame();
    main_window.show();
    return app.exec();
}
catch (std::exception& e){
    qFatal("Error %s", e.what());
}
