#include <iostream>
#include <string>

// Define a struct named Person
struct Person {
    // Data members
    std::string name;
    int age;
    double height;
};

int main() {
    // Create an instance of the Person struct
    Person person1;
    Person person2{std::string("xx"), 45, 4};

    // Assign values to the struct members
    person1.name = "John Doe";
    person1.age = 25;
    person1.height = 5.9;

    // Display the information using the struct members
    std::cout << "Person Information:" << std::endl;
    std::cout << "Name: " << person1.name << std::endl;
    std::cout << "Age: " << person1.age << " years" << std::endl;
    std::cout << "Height: " << person1.height << " feet" << std::endl;

    // Display the information using the struct members
    std::cout << "Person Information:" << std::endl;
    std::cout << "Name: " << person2.name << std::endl;
    std::cout << "Age: " << person2.age << " years" << std::endl;
    std::cout << "Height: " << person2.height << " feet" << std::endl;

    return 0;
}