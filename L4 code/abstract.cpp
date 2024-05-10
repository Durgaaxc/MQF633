#include <iostream>
#include <cmath>

using namespace std;

// Abstract base class
class Shape {

public:
    // Pure virtual function makes this class abstract
    virtual double area() const = 0; // To be implemented by derived classes
    virtual void display() const = 0; // To be implemented by derived classes

    // Virtual destructor to ensure proper cleanup in polymorphic scenarios
    virtual ~Shape() {}
};

// Derived class: Circle
class Circle : public Shape {

private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    // Implementation of virtual function for area calculation
    double area() const override {
        return 3.14 * radius * radius;
    }
    // Implementation of virtual function for displaying information
    void display() const override {
        std::cout << "Circle - Radius: " << radius << ", Area: " << area() << std::endl;
    }
};

// Derived class: Circle
class Square : public Shape {

private:
    double edge;

public:
    Square(double r) : edge(r) {}

    // Implementation of virtual function for area calculation
    double area() const override {
        return edge * edge;
    }
    // Implementation of virtual function for displaying information
    void display() const override {
        std::cout << "Sqaure - Edge: " << edge << ", Area: " << area() << std::endl;
    }
};

int main() {

    //1
    Circle myCircle(4);
    myCircle.display();

    //2 using base class type pointer for concecpt of abstract and generic
    Shape* myCircle2 = new Circle(2);
    myCircle2->display();
    
    //3
    Shape* mySquare = new Square(3);
    mySquare->display();

    //4 compiling error, base class being abstract class, cannot instantiate object !!!
    //Shape anyShape;

    return 0;
}