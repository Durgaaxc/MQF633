#include <iostream>
#include <vector>

int main() {
    // Example 1: Initializing and Populating
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Example 2: Accessing Elements
    std::cout << "First element: " << numbers[0] << std::endl;
    std::cout << "Size of the vector: " << numbers.size() << std::endl;

    // Example 3: Modifying Elements
    numbers[2] = 10;

    // Example 4: Iterating through Elements
    std::cout << "Vector elements: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Example 5: Adding Elements (push_back)
    numbers.push_back(6);
    numbers.push_back(7);

    // Example 6: Removing Elements (pop_back)
    numbers.pop_back();

    // Example 7: Finding an Element
    int target = 4;
    auto it = std::find(numbers.begin(), numbers.end(), target);

    return 0;
}