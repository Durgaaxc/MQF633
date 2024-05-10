#include <iostream>

// Template function to swap two values of any data type
template <typename T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

int main() {
    
    // Example with integers
    int x = 5, y = 10;
    std::cout << "Before swapping: x = " << x << ", y = " << y << std::endl;

    // Call the template function to swap integers
    swapValues(x, y);

    std::cout << "After swapping: x = " << x << ", y = " << y << std::endl;

    // Example with double values
    double a = 3.14, b = 2.718;
    std::cout << "Before swapping: a = " << a << ", b = " << b << std::endl;

    // Call the template function to swap doubles
    swapValues(a, b);

    std::cout << "After swapping: a = " << a << ", b = " << b << std::endl;

    return 0;
}