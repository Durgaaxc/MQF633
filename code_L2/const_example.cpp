#include <iostream>

int main() {
    // Constant variable
    const int maxAttempts = 3;

    // Normal variable
    int score = 100;

    // Constant pointer to an integer
    const int* constPointer = &score;

    // Constant reference to an integer
    const int& constReference = score;

    // Attempting to modify the constant variable will result in a compilation error
    // maxAttempts = 4;  // Error: assignment of read-only variable 'maxAttempts'

    // Attempting to modify the value through the constant pointer or reference is not allowed
    // (*constPointer)++;  // Error: increment of read-only location
    // constReference++;    // Error: increment of read-only reference

    // Displaying values
    std::cout << "Max Attempts: " << maxAttempts << std::endl;
    std::cout << "Score: " << score << std::endl;
    return 0;
}