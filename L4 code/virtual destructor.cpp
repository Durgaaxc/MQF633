#include <iostream>

// Base class
class Base {

public:
    Base() {
        std::cout << "Base class constructor" << std::endl;
    }

    // Virtual destructor, if do not use virtual, there will be memory leak
    virtual ~Base() {
        std::cout << "Base class destructor" << std::endl;
    }
};

// Derived class
class Derived : public Base {

public:
    Derived() {
        std::cout << "Derived class constructor" << std::endl;
    }

    // Destructor (implicitly virtual due to the virtual destructor in the base class)
    ~Derived() {
        std::cout << "Derived class destructor" << std::endl;
    }
};

int main() {
    
    //Creating a derived class object using derived class pointer
    Derived* dPtr = new Derived();
    delete dPtr;

    // Creating a derived class object using a base class pointer
    Base* basePtr = new Derived();
    
    // Deleting the object through the base class pointer
    delete basePtr;
    
    return 0;
}