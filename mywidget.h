#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include "QuadTree.h"

class MyWidget : public QWidget {
    QuadTree quadTree;

public:
    MyWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    void drawQuadTree(QPainter &painter, const QuadTree &qt);
    void drawNode(QPainter &painter, const QuadTree::Node *node);
};

#endif // MYWIDGET_H
