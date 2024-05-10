#include <iostream>

// Function with default arguments
int multiply(int a, int b = 2, int c = 1) {
    return a * b * c;
}

int main() {
    // Example 1: Using all parameters
    int result1 = multiply(3, 4, 2);
    std::cout << "Result 1: " << result1 << std::endl;

    // Example 2: Using only the first parameter
    int result2 = multiply(5);
    std::cout << "Result 2: " << result2 << std::endl;

    // Example 3: Using the first and second parameters
    int result3 = multiply(2, 3);
    std::cout << "Result 3: " << result3 << std::endl;

    return 0;
}