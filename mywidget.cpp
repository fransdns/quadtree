#include "MyWidget.h"
#include <QPainter>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent), quadTree({0, 0}, {width(), height()}) {}

void MyWidget::mousePressEvent(QMouseEvent *event) {
    QPointF position = event->position();
    Point clickedPoint = { static_cast<double>(position.x()), static_cast<double>(position.y()), true }; // Marcar como clickeado
    quadTree.insert(clickedPoint);
    update(); // Trigger a repaint
}

void MyWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    drawQuadTree(painter, quadTree);
}

void MyWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    quadTree = QuadTree({0, 0}, {width(), height()}); // Redimensionar el QuadTree
    update(); // Trigger a repaint to reflect the new size
}

void MyWidget::drawQuadTree(QPainter &painter, const QuadTree &qt) {
    drawNode(painter, qt.getRoot());
}

void MyWidget::drawNode(QPainter &painter, const QuadTree::Node *node) {
    if (!node) return;

    QRect rect(node->topLeft.x, node->topLeft.y, node->bottomRight.x - node->topLeft.x, node->bottomRight.y - node->topLeft.y);
    painter.drawRect(rect);

    // Draw the point in red if it exists and is clicked
    if (node->point && node->point->isClicked) {
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPointF(node->point->x, node->point->y), 3, 3);
        painter.setBrush(Qt::NoBrush); // Reset brush to no brush
    }

    // Recursively draw the child nodes
    if (node->topLeftTree) drawNode(painter, node->topLeftTree->getRoot());
    if (node->topRightTree) drawNode(painter, node->topRightTree->getRoot());
    if (node->bottomLeftTree) drawNode(painter, node->bottomLeftTree->getRoot());
    if (node->bottomRightTree) drawNode(painter, node->bottomRightTree->getRoot());
}
