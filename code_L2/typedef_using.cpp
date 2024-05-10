#include <iostream>

// Original data type
typedef double Distance;

// Equivalent to typedef double Distance;
// using Distance = double;

int main() {
    // Using the typedef alias
    Distance length = 10.5;
    Distance width = 5.2;

    // Calculating the area
    Distance area = length * width;

    // Displaying the result
    std::cout << "Length: " << length << std::endl;
    std::cout << "Width: " << width << std::endl;
    std::cout << "Area: " << area << std::endl;

    return 0;
}