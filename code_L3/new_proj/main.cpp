#include <iostream>
#include "math_operation.h"

using namespace std;

int main () {

    int x =10, y = 20;
    int result = add(x,y);
    cout << "add result: " << result<<endl;

    result = subtract(x , y);
    cout << "substract result: " << result<<endl;

    result = multiply(x , y);
    cout << "multiply result: " << result<<endl;

    return 0;

}