#include <iostream>
#include <string>

int main() {
    // Example 1: Initializing and Assigning
    std::string greeting = "Hello, ";
    std::string name = "John";

    // Example 2: Concatenation
    std::string fullGreeting = greeting + name;

    // Example 3: String Length
    std::cout << "Length of the greeting: " << greeting.length() << std::endl;

    // Example 4: Accessing Characters
    char firstChar = name[0];
    std::cout << "First character of the name: " << firstChar << std::endl;

    // Example 5: Iterating through characters
    std::cout << "Characters in the name: ";
    for (char ch : name) {
        std::cout << ch << " ";
    }
    std::cout << std::endl;

    // Example 6: Substring
    std::string subString = fullGreeting.substr(0, 5);

    // Example 7: Find
    size_t position = fullGreeting.find("John");
    if (position != std::string::npos) {
        std::cout << "Substring 'John' found at position: " << position << std::endl;
    } else {
        std::cout << "Substring 'John' not found." << std::endl;
    }
    return 0;
}