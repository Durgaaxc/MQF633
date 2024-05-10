#include <iostream>

// Function that throws an exception
void divideNumbers(int numerator, int denominator) {
    if (denominator == 0) {
        // Throw an exception if the denominator is zero
        throw std::runtime_error("Error: Division by zero");
    }

    // Perform the division if the denominator is not zero
    int result = numerator / denominator;
    std::cout << "Result of division: " << result << std::endl;
}

int main() {
    try {
        // Call a function that may throw an exception
        divideNumbers(10, 2);
        
        // Uncomment the line below to test the exception case
        divideNumbers(5, 0);
    } catch (const std::exception& e) {
        // Catch the exception and handle it
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}