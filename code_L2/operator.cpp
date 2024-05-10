#include <iostream>

int main() {

    if (1) {
        int a = 10, b = 5;

        // Addition
        int sum = a + b;

        // Subtraction
        int difference = a - b;

        // Multiplication
        int product = a * b;

        // Division
        int quotient = a / b;

        // Modulus (remainder)
        int remainder = a % b;

        std::cout << "Sum: " << sum << std::endl;
        std::cout << "Difference: " << difference << std::endl;
        std::cout << "Product: " << product << std::endl;
        std::cout << "Quotient: " << quotient << std::endl;
        std::cout << "Remainder: " << remainder << std::endl;
    }

    if(0) {
        int x = 5, y = 10;

        // Equal to
        bool isEqual = (x == y);

        // Not equal to
        bool notEqual = (x != y);

        // Greater than
        bool greaterThan = (x > y);

        // Less than
        bool lessThan = (x < y);

        // Greater than or equal to
        bool greaterOrEqual = (x >= y);

        // Less than or equal to
        bool lessOrEqual = (x <= y);

        std::cout << "Equal: " << isEqual << std::endl;
        std::cout << "Not Equal: " << notEqual << std::endl;
        std::cout << "Greater Than: " << greaterThan << std::endl;
        std::cout << "Less Than: " << lessThan << std::endl;
        std::cout << "Greater or Equal: " << greaterOrEqual << std::endl;
        std::cout << "Less or Equal: " << lessOrEqual << std::endl;
    }

    return 0;
}