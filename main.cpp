#include <iostream>
#include <vector>

using namespace std;

// Define una clase Point para representar puntos en el espacio 2D
class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

// Define una clase Node para representar nodos en el quadtree
class Node {
public:
    Point* point;
    int xMin, yMin, xMax, yMax;
    Node* NW;
    Node* NE;
    Node* SW;
    Node* SE;

    Node(int xMin, int yMin, int xMax, int yMax)
        : point(nullptr), xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax),
        NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}

    bool isLeaf() {
        return NW == nullptr && NE == nullptr && SW == nullptr && SE == nullptr;
    }
};

// Define una clase QuadTree para representar el quadtree
class QuadTree {
private:
    Node* root;

    void insert(Node*& node, Point* point) {
        if (node == nullptr) {
            return;
        }

        if (node->isLeaf()) {
            if (node->point == nullptr) {
                node->point = point;
                return;
            }
            else {
                Point* oldPoint = node->point;
                node->point = nullptr;
                subdivide(node);

                // Insertar el punto antiguo
                insert(node, oldPoint);
                // Insertar el nuevo punto
                insert(node, point);
            }
        }
        else {
            if (point->x <= (node->xMin + node->xMax) / 2) {
                if (point->y <= (node->yMin + node->yMax) / 2) {
                    insert(node->NW, point);
                }
                else {
                    insert(node->SW, point);
                }
            }
            else {
                if (point->y <= (node->yMin + node->yMax) / 2) {
                    insert(node->NE, point);
                }
                else {
                    insert(node->SE, point);
                }
            }
        }
    }

    void subdivide(Node*& node) {
        int midX = (node->xMin + node->xMax) / 2;
        int midY = (node->yMin + node->yMax) / 2;

        node->NW = new Node(node->xMin, node->yMin, midX, midY);
        node->NE = new Node(midX, node->yMin, node->xMax, midY);
        node->SW = new Node(node->xMin, midY, midX, node->yMax);
        node->SE = new Node(midX, midY, node->xMax, node->yMax);
    }

public:
    QuadTree(int xMin, int yMin, int xMax, int yMax) {
        root = new Node(xMin, yMin, xMax, yMax);
    }

    void insert(Point* point) {
        insert(root, point);
    }

    bool search(Point* point) {
        return search(root, point);
    }

    bool search(Node* node, Point* point) {
        if (node == nullptr) {
            return false;
        }

        if (node->isLeaf()) {
            return node->point != nullptr && node->point->x == point->x && node->point->y == point->y;
        }

        if (point->x <= (node->xMin + node->xMax) / 2) {
            if (point->y <= (node->yMin + node->yMax) / 2) {
                return search(node->NW, point);
            }
            else {
                return search(node->SW, point);
            }
        }
        else {
            if (point->y <= (node->yMin + node->yMax) / 2) {
                return search(node->NE, point);
            }
            else {
                return search(node->SE, point);
            }
        }
    }
};

int main() {
    QuadTree qt(0, 0, 100, 100);

    qt.insert(new Point(10, 10));
    qt.insert(new Point(50, 50));
    qt.insert(new Point(70, 80));

    cout << "Searching for (10, 10): " << (qt.search(new Point(10, 10)) ? "Found" : "Not Found") << endl;
    cout << "Searching for (15, 15): " << (qt.search(new Point(15, 15)) ? "Found" : "Not Found") << endl;

    return 0;
}
