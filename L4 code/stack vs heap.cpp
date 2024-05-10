#include <iostream>

void stackExample() {
    int stackVar = 5; // Variable allocated on the stack
    // ...
} // stackVar is automatically deallocated when the function exits

void heapExample() {
    int* heapVar = new int; // Variable allocated on the heap
    // ...
    delete heapVar; // Explicitly deallocate memory to avoid memory leaks
}

int main() {

    stackExample();
    heapExample();

    // All these variables get memory allocated on stack
    int a;
    int b[10];
    int n = 20;
    int c[n];

    int* p = new int[10]; // allocate memory in heap for 10 integer
    *p = 10;
    p[15] = 9;
    delete [] p;

    return 0;
}