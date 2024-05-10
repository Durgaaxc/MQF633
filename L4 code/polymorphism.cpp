#include <iostream>

using namespace std;


class Shape {

public:
    virtual void draw() {
        cout << "Drawing a shape" << endl;
    }
};

class Circle : public Shape {

public:
    void draw() override {
        cout << "Drawing a circle" << endl;
    }
};

class Square : public Shape {

public:
    void draw() override {
        cout << "Drawing a square" << endl;
    }
};

int main() {
    
    Shape* shape0 = new Shape();
    Shape* shape1 = new Circle(); //pay attention
    Shape* shape2 = new Square(); //pay attention
    shape0->draw();
    shape1->draw();  // Calls draw() from Circle
    shape2->draw();  // Calls draw() from Square

    delete shape0;
    delete shape1;
    delete shape2;

    return 0;
}