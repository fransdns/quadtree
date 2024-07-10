#include "QuadTree.h"
#include <iostream>

QuadTree::Node::Node(Point tl, Point br) : topLeft(tl), bottomRight(br), point(nullptr),
    topLeftTree(nullptr), topRightTree(nullptr),
    bottomLeftTree(nullptr), bottomRightTree(nullptr) {}

QuadTree::QuadTree(Point topLeft, Point bottomRight) {
    root = new Node(topLeft, bottomRight);
}

void QuadTree::insert(Point point) {
    insert(root, point);
}

void QuadTree::insert(Node *node, Point point) {
    if (!node) return;

    if (!node->point) {
        node->point = new Point(point);
    } else {
        if (point.x <= (node->topLeft.x + node->bottomRight.x) / 2) {
            if (point.y <= (node->topLeft.y + node->bottomRight.y) / 2) {
                if (!node->topLeftTree) node->topLeftTree = new QuadTree({node->topLeft.x, node->topLeft.y}, {(node->topLeft.x + node->bottomRight.x) / 2, (node->topLeft.y + node->bottomRight.y) / 2});
                insert(node->topLeftTree->root, point);
            } else {
                if (!node->bottomLeftTree) node->bottomLeftTree = new QuadTree({node->topLeft.x, (node->topLeft.y + node->bottomRight.y) / 2}, {(node->topLeft.x + node->bottomRight.x) / 2, node->bottomRight.y});
                insert(node->bottomLeftTree->root, point);
            }
        } else {
            if (point.y <= (node->topLeft.y + node->bottomRight.y) / 2) {
                if (!node->topRightTree) node->topRightTree = new QuadTree({(node->topLeft.x + node->bottomRight.x) / 2, node->topLeft.y}, {node->bottomRight.x, (node->topLeft.y + node->bottomRight.y) / 2});
                insert(node->topRightTree->root, point);
            } else {
                if (!node->bottomRightTree) node->bottomRightTree = new QuadTree({(node->topLeft.x + node->bottomRight.x) / 2, (node->topLeft.y + node->bottomRight.y) / 2}, {node->bottomRight.x, node->bottomRight.y});
                insert(node->bottomRightTree->root, point);
            }
        }
    }
}

const QuadTree::Node* QuadTree::getRoot() const {
    return root;
}
