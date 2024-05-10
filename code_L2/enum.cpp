#include <iostream>

// Define an enumeration named Days
enum Days {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

int main() {
    // Declare a variable of type Days
    Days today = Wednesday;
    
    // Switch statement using the enum values
    switch (today) {
        case Sunday:
            std::cout << "It's Sunday!" << std::endl;
            break;
        case Monday:
            std::cout << "It's Monday!" << std::endl;
            break;
        case Tuesday:
            std::cout << "It's Tuesday!" << std::endl;
            break;
        case Wednesday:
            std::cout << "It's Wednesday!" << std::endl;
            break;
        case Thursday:
            std::cout << "It's Thursday!" << std::endl;
            break;
        case Friday:
            std::cout << "It's Friday!" << std::endl;
            break;
        case Saturday:
            std::cout << "It's Saturday!" << std::endl;
            break;
    }
    return 0;
}