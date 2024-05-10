#include <iostream>

// Define a structure named Point
struct Point {
    int x;
    int y;
};

// Function that returns a Point structure
Point createPoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Point addPoint(Point& p1, Point& p2) {
    Point p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    return p;
}

int main() {
    // Call the function and store the returned Point structure
    Point myPoint = createPoint(3, 7);

    // Access the members of the returned structure
    std::cout << "X-coordinate: " << myPoint.x << std::endl;
    std::cout << "Y-coordinate: " << myPoint.y << std::endl;

    Point otherPoint = createPoint(5, 5);
    Point combinedPoint = addPoint(myPoint, otherPoint);
    // Access the members of the returned structure
    std::cout << "X-coordinate: " << combinedPoint.x << std::endl;
    std::cout << "Y-coordinate: " << combinedPoint.y << std::endl;

    return 0;
}