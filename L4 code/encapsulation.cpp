#include <iostream>

using namespace std;

static const double PAI  = 3.14159265;

class Circle {

private://encapsulate private member from outside access
    double radius;

public:
    // Setter method
    void setRadius(double r) {
        if (r > 0) {
            radius = r;
        } else {
            cout << "Invalid radius" << endl;
        }
    }

    // Getter method
    double getArea() {
        return PAI * radius * radius;
    }

    // Getter method
    inline double getRadius() { return radius;}
};

int main() {
    Circle myCircle;
    myCircle.setRadius(5.0);

    cout << "Radius of the cirlce: "<< myCircle.getRadius() << endl;
    cout << "Area of the circle: " << myCircle.getArea() << endl;

    return 0;
}