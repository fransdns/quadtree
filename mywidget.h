#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QResizeEvent>
#include "QuadTree.h"

class MyWidget : public QWidget {
    Q_OBJECT

    QuadTree quadTree;

public:
    MyWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override; // Declaración del método resizeEvent

private:
    void drawQuadTree(QPainter &painter, const QuadTree &qt);
    void drawNode(QPainter &painter, const QuadTree::Node *node);
};

#endif // MYWIDGET_H

