#include <iostream>

using namespace std;

class ShallowCopy {
private:
    int* data;

public:
    ShallowCopy(int val) {
        data = new int(val);
    }

    // Shallow copy constructor
    ShallowCopy(const ShallowCopy& other) : data(other.data) {}

    // Shallow copy assignment operator
    ShallowCopy& operator=(const ShallowCopy& other) {
        if (this != &other) {
            delete data; // Deallocate old data
            data = other.data;
        }
        return *this;
    }
    inline void setData(int newValue) const { *data = newValue;};
    inline int getData() const {return *data;};
    
    ~ShallowCopy() {
        delete data;
    }
};

class DeepCopy {
private:
    int* data;

public:
    DeepCopy(int val) {
        data = new int(val);
    }

    // Deep copy constructor
    DeepCopy(const DeepCopy& other) : data(new int(*(other.data))) {}

    // Deep copy assignment operator
    DeepCopy& operator=(const DeepCopy& other) {
        if (this != &other) {
            delete data; // Deallocate old data
            data = new int(*(other.data));
        }
        return *this;
    }
    inline void setData(int newValue) const { *data = newValue;};
    inline int getData() const {return *data;};

    ~DeepCopy() {
        delete data;
    }
};

int main () {

    auto s_obj = ShallowCopy(10);
    auto s_obj_copy1(s_obj);
    auto s_obj_copy2=s_obj;
    s_obj.setData(6);
    cout<< s_obj.getData() <<endl;
    cout<< s_obj_copy1.getData() <<endl;
    cout<< s_obj_copy2.getData() <<endl;

    auto d_obj = DeepCopy(10);
    auto d_obj_copy1(d_obj);
    auto d_obj_copy2=d_obj;
    d_obj.setData(5);

    cout<< d_obj.getData() <<endl;
    cout<< d_obj_copy1.getData() <<endl;
    cout<< d_obj_copy2.getData() <<endl;

    return 0;

}