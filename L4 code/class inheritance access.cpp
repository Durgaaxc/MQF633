#include <iostream>

// Base class with public, private, and protected members
class Base {
public:
    int publicVar;     // Public member
    void publicMethod() {
        std::cout << "Public method in Base class" << std::endl;
    }

private:
    int privateVar;    // Private member
    void privateMethod() {
        std::cout << "Private method in Base class" << std::endl;
    }

protected:
    int protectedVar;  // Protected member
    void protectedMethod() {
        std::cout << "Protected method in Base class" << std::endl;
    }
};

// Derived class
class Derived : public Base {

public:
    void accessBaseMembers() {
        // Accessing public members of the Base class
        publicVar = 10;
        publicMethod();

        // Accessing protected members of the Base class
        protectedVar = 20;
        protectedMethod();

        // Cannot access private members of the Base class
        // privateVar = 30;  // This would result in a compilation error
        // privateMethod();  // This would result in a compilation error
    }
};

int main() {
    // Accessing public members of the Base class
    Base baseObj;
    baseObj.publicVar = 5;
    baseObj.publicMethod();

    // Cannot access private and protected members from outside the class
    // baseObj.privateVar = 15;  // This would result in a compilation error
    // baseObj.privateMethod();  // This would result in a compilation error
    // baseObj.protectedVar = 25;  // This would result in a compilation error
    // baseObj.protectedMethod();  // This would result in a compilation error

    // Accessing members through a derived class
    Derived derivedObj;
    derivedObj.accessBaseMembers();

    return 0;
}
