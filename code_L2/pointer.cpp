#include <iostream>

using namespace std;
int main() {

    if (true) {
        // Declare a variable
    int number = 42;

    // Declare a pointer to an integer and initialize it with the address of 'number'
    int *pointerToNumber = &number;

    // Display the value of 'number' and the memory address it occupies
    std::cout << "Value of 'number': " << number << std::endl;
    std::cout << "Memory address of 'number': " << &number << std::endl;

    // Display the value of 'pointerToNumber' (memory address)
    std::cout << "Value of 'pointerToNumber' (memory address): " << pointerToNumber << std::endl;

    // Access the value of 'number' through the pointer and display it
    std::cout << "Value of 'number' accessed through the pointer: " << *pointerToNumber << std::endl;

    }
    
    if (1) {
 
    // Declare a variable
    int number = 42;

    // Declare a reference to an integer and initialize it with the variable 'number'
    int& referenceToNumber = number;

    // Display the value of 'number' and the value through the reference
    std::cout << "Value of 'number': " << number << std::endl;
    std::cout << "Value through the reference: " << referenceToNumber << std::endl;

    // Modify the value through the reference
    referenceToNumber = 99;

    // Display the modified value of 'number'
    std::cout << "Modified value of 'number': " << number << std::endl;
    }
    
    //pointer vs reference
    if(0){


    }

    return 0;
}
    

