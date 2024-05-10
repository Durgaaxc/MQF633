#include <iostream>
#include <string>

// Define a class named Student
class Student {
public:
//private:
    // Public data members
    std::string name;
    int age;
    double GPA;
//public:
    // Public member function to display student information
    //void updateName(std::string _name) { name: _name;};
    void displayInfo() {
        std::cout << "Student Information:" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << " years" << std::endl;
        std::cout << "GPA: " << GPA << std::endl;
    }
};


int main() {
    // Create an instance of the Person struct
    // Create an instance of the Student class
    Student student1;

    // Assign values to the class members
    student1.name = "Alice Smith";
    student1.age = 20;
    student1.GPA = 3.75;

    // Call the member function to display student information
    student1.displayInfo();

    return 0;
}