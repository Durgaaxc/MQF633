#include <iostream>

// Recursive function to calculate the factorial of a number
unsigned long factorial(int n) {
    if (n < 0)
        throw std::runtime_error("there is no factorial for negative number!!");
    // Base case: factorial of 0 is 1
    if (n == 0 || n == 1) {
        return 1;
    } else {
        // Recursive case: n! = n * (n-1)!
        return static_cast<unsigned long>(n) * factorial(n - 1);
    }
}

// None Recursive function 
unsigned long factorial2(int n) {
    // Base case: factorial of 0 is 1
    if (n < 0)
        throw std::runtime_error("there is no factorial for negative number!!");
    if (n == 0 || n == 1) {
        return 1;
    } else {
        // Recursive case: n! = n * (n-1)!
        unsigned long result=n;
        while (n>=2) {
            n--;
            result *=n;        
        }      
        return result;
    }
}

int main() {
    // Calculate and display the factorial of 5
    int number = 10;
    unsigned long result = factorial(number);

    std::cout << "Factorial of " << number << " is: " << result << std::endl;

    unsigned long result2 = factorial2(number);
    std::cout << "Factorial2 of " << number << " is: " << result2 << std::endl;

    return 0;
}