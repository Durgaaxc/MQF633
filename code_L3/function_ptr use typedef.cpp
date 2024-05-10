#include <iostream>

// Function to add two numbers
int add(int a, int b) {
    return a + b;
}

// Function to subtract two numbers
int subtract(int a, int b) {
    return a - b;
}

// Define a typedef for a function pointer type
typedef int (*BinaryOperation)(int, int);

// Function that performs an operation using a function pointer
int performOperation(int a, int b, BinaryOperation operation) {
    return operation(a, b);
}

int main() {
    // Declare function pointers using the typedef
    BinaryOperation addPtr = add;
    BinaryOperation subtractPtr = subtract;

    // Use the function pointers
    std::cout << "Addition: " << performOperation(5, 3, addPtr) << std::endl;
    std::cout << "Subtraction: " << performOperation(5, 3, subtractPtr) << std::endl;

    return 0;
}