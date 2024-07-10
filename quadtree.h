#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>

struct Point {
    double x, y;
};

class QuadTree {
public:
    struct Node {
        Point topLeft, bottomRight;
        Point *point;
        QuadTree *topLeftTree, *topRightTree, *bottomLeftTree, *bottomRightTree;

        Node(Point tl, Point br);
    };

private:
    Node *root;

public:
    QuadTree(Point topLeft, Point bottomRight);
    void insert(Point point);
    const Node* getRoot() const;

private:
    void insert(Node *node, Point point);
};

#endif // QUADTREE_H
