#include <iostream>

using namespace std;
int main() {

    // Example of pointer
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
    
    // Example of reference
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

    // Pointer vs Rerence
    if (1) {

        int arr[] = {10, 20, 30, 40, 50};
        int *ptr = arr;
        std::cout << "Value at the position: " << *ptr << std::endl;

        // Pointer arithmetic
        ptr = ptr + 2;  // Increment by 2 elements
        std::cout << "Value at the incremented position: " << *ptr << std::endl;

        // Array indexing using pointer arithmetic
        int thirdElement = *(ptr + 1);  // Access the third element
        std::cout << "Value of the third element: " << thirdElement << std::endl;

        // Comparison of pointers
        int *ptr2 = arr + 2;
        if (ptr == ptr2) {
            std::cout << "Pointers are equal." << std::endl;
            } else {
            std::cout << "Pointers are not equal." << std::endl;
            }

    }

    return 0;
}
    

