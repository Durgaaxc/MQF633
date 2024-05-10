#include <iostream>
using namespace std;

template <typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;

public:
    Pair(T1 a, T2 b) {
        first=a;
        second=b;
    }

    T1 GetFirst() {
        return first;
    }

    T2 GetSecond() {
        return second;
    }

};

int main() {
    
    Pair<int, double> pair1(10, 3.14);
    cout << "First: " << pair1.GetFirst() << ", Second: " << pair1.GetSecond() << endl;

    Pair<string, bool> pair2("hello", true);
    cout << "First: " << pair2.GetFirst() << ", Second: " << pair2.GetSecond() << endl;

    return 0;
}