#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Example 1: Lambda expression for a simple addition function
    auto add = [](int a, int b) { return a + b; };

    std::cout << "Sum: " << add(3, 4) << std::endl;

    // Example 2: Lambda expression for a predicate in a standard algorithm
    std::vector<int> numbers = {5, 2, 8, 1, 7, 3};
    
    // Sorting the vector in descending order using a lambda expression
    // std::sort requires a comparator function for the container
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) { return a > b; });

    std::cout << "Sorted numbers in descending order: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Example 3: Lambda expression capturing variables from the surrounding scope
    // [] it means capture list
    int base = 10;
    auto addWithBase = [base](int value) { return base + value; };

    std::cout << "Result with captured base: " << addWithBase(5) << std::endl;

    return 0;
}