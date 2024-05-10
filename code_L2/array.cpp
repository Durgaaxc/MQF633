#include <iostream>

using namespace std;
int main()
{
    //example of integer array
    const int arrSize = 5;
    int myArr[arrSize] = {10, 20, 30, 40, 50};
    std::cout<< "Element of my array:" <<endl;
    for (size_t i=0; i<arrSize; i++){
        std::cout<< "Element "<< i << ":" << myArr[i] <<endl;
    }
    
    //example of char array
    char myArr2[12] = {'*', '*'};
    char myArr3[] = "Hello";
    
    cout<< "Element of my array:" <<endl;
    for (size_t i = 0; i< 12; i++){
        cout<< "Element in arr2 "<< i << ":" << myArr2[i] <<endl;
    }
    for (size_t i = 0; i< 5; i++){
        cout<< "Element in arr3 "<< i << ":" << myArr3[i] <<endl;
    }

    return 0;
}
        
    

