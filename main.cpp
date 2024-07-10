#include <QApplication>
#include "MyWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWidget widget;
    widget.resize(800, 600);
    widget.show();

    return app.exec();
}
