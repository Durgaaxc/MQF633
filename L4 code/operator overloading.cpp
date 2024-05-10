#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r, double i) : real(r), imaginary(i) {}

    // Overloading the '+' operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }

    // Display the complex number
    void display() const {
        std::cout << real << " + " << imaginary << "i" << std::endl;
    }
};

int main() {
    // Creating two complex numbers
    Complex c1(3.0, 4.0);
    Complex c2(1.5, 2.5);

    // Using the overloaded '+' operator
    Complex result = c1 + c2;

    // Displaying the result
    std::cout << "Result: ";
    result.display();

    return 0;
}