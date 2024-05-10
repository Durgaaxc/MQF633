#include <iostream>
#include <string>

using namespace std;

//a class without default constructor
class Book {
public:
    Book(std::string name_) {
        name=name_;
    }
    
    std::string name;
};

class Book2 {
public:
    Book2(std::string name_): name(name_){
}
    
private:
    const std::string name;
};

//a class where has book class as member
class Student {
public:
    
    // Constructor by initializer list
    // for member does not have default contructor
    // with refenerce as member
    Student(string name, int age, std::string bookName, int i) : 
    studentName(name), 
    studentAge(age), 
    book(bookName), 
    numOfbooks(i)
    {
        cout << "Student object created by initializer..." << endl;
    }

    // Destructor
    ~Student() {
        cout << "Student obj with name of "<< studentName << " is destroyed ..." << endl;
    }

    void displayInfo() {
        cout << "Name: " << studentName << ", Age: " << studentAge 
        << " who has book: " << book.name << endl;
    }

private:
    string studentName;
    int studentAge;
    Book book;
    int& numOfbooks;
};

int main() {
    // Create an object with constructor
    Student myStudent("John", 20, "a book", 1);

    // Call a member function
    myStudent.displayInfo();

    return 0;
}