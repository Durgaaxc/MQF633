#include <iostream>

using namespace std;

// Example of a function pointer declaration
int (*addPtr) (int, int);

// Example of assigning function addresses to pointers
int add(int a, int b) {
    return a + b;
}

// Example of using function pointers as parameters
void performOperation(int a, int b, int (*operation)(int, int)) {
    int result = operation(a, b);
    std::cout << "Result: " << result << std::endl;
}

// example of callback function
void callbackFunction() {
    std::cout << "Callback function called." << std::endl;
}

void performCallback(void (*callback)()) {
    callback();
}


int main() { 

    //example 1
    if (true) {
        addPtr = &add;  // or addPtr = add;

        // Example of invoking a function through a pointer
        int result1 = (*addPtr)(3, 4);
        cout<< "result of add: " << result1 <<endl;
        // or
        int result2 = addPtr(5, 6);
        cout<< "result of add: " << result2 <<endl;

    }

    //example2 : pass function pointer as argument of other function
    if (true) {
        performOperation(5, 3, addPtr);
    }

    //example 3: using function pointer as callbacks
    if (true) {
        performCallback(callbackFunction);
    } 
    
    return 0;
}