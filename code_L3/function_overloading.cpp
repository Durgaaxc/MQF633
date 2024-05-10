#include <iostream>
// Function overloading in C++ means function with same name but different argument list
// Function to add two integers
int add(int a, int b) {
    return a + b;
}
// Function to concatenate two strings
std::string add(std::string str1, std::string str2) {
    return str1 + str2;
}
// Function to add three integers
int add(int a, int b, int c) {
    return a + b + c;
}

int main() {
    // Example 1: Adding two integers
    int sum1 = add(3, 5);
    std::cout << "Sum of two integers: " << sum1 << std::endl;

    // Example 2: Concatenating two strings
    std::string resultStr = add("Hello, ", "World!");
    std::cout << "Concatenated string: " << resultStr << std::endl;

    // Example 3: Adding three integers
    int sum2 = add(2, 4, 6);
    std::cout << "Sum of three integers: " << sum2 << std::endl;

    return 0;
}