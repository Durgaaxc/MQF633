#include <iostream>

// Template class definition
template <typename T>
class Container {
private:
    T data;

public:
    Container(T value) : data(value) {}
    
    T getValue() const {
        return data;
    }
};

int main() {
    
    // Instantiate Container with int
    Container<int> intContainer(42);
    std::cout << "Integer Value: " << intContainer.getValue() << std::endl;

    // Instantiate Container with double
    Container<double> doubleContainer(3.14);
    std::cout << "Double Value: " << doubleContainer.getValue() << std::endl;

    // Instantiate Container with string
    Container<std::string> stringContainer("Hello, C++!");
    std::cout << "String Value: " << stringContainer.getValue() << std::endl;

    return 0;
}