#include <iostream>

// Global variable with file scope and static duration
int globalVariable = 10;

void exampleFunction() {
    // Local variable with function scope and automatic duration
    int localVar = 5;

    // Accessing the global variable
    std::cout << "Inside function - Global variable: " << globalVariable << std::endl;

    // Accessing the local variable
    std::cout << "Inside function - Local variable: " << localVar << std::endl;
}

int main() {
    // Accessing the global variable
    std::cout << "In main - Global variable: " << globalVariable << std::endl;
    
    // Local variable with block scope and automatic duration
    int localVar = 7;
    
    // Accessing the local variable
    std::cout << "In main - Local variable: " << localVar << std::endl;
    
    // Call the function
    exampleFunction();
    
    std::cout << "In main after function - Local variable: " << localVar << std::endl;

    return 0;
}