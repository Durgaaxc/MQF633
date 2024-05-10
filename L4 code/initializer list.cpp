#include <iostream>
using namespace std;

// Define a class
class Car {
public:
    // Member variables
    string brand;
    int year;

    // Member function (method)
    void displayInfo() {
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
};

int main() {
    // Create an object of the class Car
    Car myCar;

    // Access and modify member variables
    myCar.brand = "Toyota";
    myCar.year = 2022;

    // Call a member function
    myCar.displayInfo();

    //another way of create object, allocate a hea memory and create a pointer point to it
    Car* yourCar = new Car();
    yourCar->brand = "BMW";
    yourCar->year = 2023;
    yourCar->displayInfo();

    delete yourCar;

    return 0;
}