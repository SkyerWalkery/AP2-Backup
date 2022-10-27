#include <QApplication>
#include <QLabel>
#include "GameField.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameField field;
    field.loadFieldFromFile("FieldData/field.txt");
    QGraphicsView view;
    // view.setRenderHint(QPainter::Antialiasing);
    view.setScene(&field);
    QRectF rect = field.sceneRect();
    qreal margin = 32;
    rect.setWidth(rect.width() + margin);
    rect.setHeight(rect.height() + margin);
    view.setFixedSize(rect.size().toSize());
    view.show();
    return app.exec();
}
