#include <iostream>

// Function that returns a pointer to an integer
int* createInteger() {
    // Dynamically allocate memory for an integer
    int* ptr = new int;
    
    // Initialize the value
    *ptr = 42;

    // Return the pointer
    return ptr;
}

int main() {
    // Call the function and get the returned pointer
    int* myIntegerPtr = createInteger();

    // Access the value through the pointer
    std::cout << "Value: " << *myIntegerPtr << std::endl;

    // Don't forget to free the allocated memory to avoid memory leaks
    delete myIntegerPtr;

    return 0;
}