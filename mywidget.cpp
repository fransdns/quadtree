#include "MyWidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), quadTree({0, 0}, {width(), height()}) {}

void MyWidget::mousePressEvent(QMouseEvent *event) {
    Point point = { static_cast<double>(event->x()), static_cast<double>(event->y()) };
    quadTree.insert(point);
    update(); // Trigger a repaint
}

void MyWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    drawQuadTree(painter, quadTree);
}

void MyWidget::drawQuadTree(QPainter &painter, const QuadTree &qt) {
    drawNode(painter, qt.getRoot());
}

void MyWidget::drawNode(QPainter &painter, const QuadTree::Node *node) {
    if (!node) return;

    QRect rect(node->topLeft.x, node->topLeft.y, node->bottomRight.x - node->topLeft.x, node->bottomRight.y - node->topLeft.y);
    painter.drawRect(rect);

    if (node->topLeftTree) drawNode(painter, node->topLeftTree->getRoot());
    if (node->topRightTree) drawNode(painter, node->topRightTree->getRoot());
    if (node->bottomLeftTree) drawNode(painter, node->bottomLeftTree->getRoot());
    if (node->bottomRightTree) drawNode(painter, node->bottomRightTree->getRoot());
}
