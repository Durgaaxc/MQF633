#include <iostream>

using namespace std;


class Animal {

public:
    void eat() {
        cout << "Animal is eating" << endl;
    }
};

class Dog : public Animal {

public:
    void bark() {
        cout << "Dog is barking" << endl;
    }
};

int main() {
    Dog myDog;
    myDog.eat();   // Inherited from Animal class
    myDog.bark();

    return 0;
}