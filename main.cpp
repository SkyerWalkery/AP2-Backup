#include <QApplication>
#include <QLabel>
#include "GameField.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameField field;
    field.loadFieldFromFile("FieldData/field.txt");
    field.loadCharacterOptionFromFile("");
    field.initOptionUi();
    QGraphicsView view;
    // view.setRenderHint(QPainter::Antialiasing);
    view.setScene(&field);
    QRectF rect = field.sceneRect();
    qreal margin = 64;
    rect.setWidth(rect.width() + margin);
    rect.setHeight(rect.height() + margin);
    view.setFixedSize(rect.size().toSize());
    field.debugStart();
    view.show();
    return app.exec();
}
