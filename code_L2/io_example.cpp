#include <iostream>
#include <fstream>
#include <string>

int main() {

    if (1) {
    // Output: Displaying text to the console
    std::cout << "Enter your name: ";

    // Input: Reading user input using std::cin
    std::string name;
    std::getline(std::cin, name);

    // Output: Displaying the user's name
    std::cout << "Hello, " << name << "!" << std::endl;

    // Input: Reading numeric input
    std::cout << "Enter your age: ";
    int age;
    std::cin >> age;

    // Output: Displaying the user's age
    std::cout << "You are " << age << " years old." << std::endl;

    return 0;
    }

    if (0){
        // Writing to a file
        std::ofstream outputFile("output.txt");
        if (outputFile.is_open()) {
            std::cout << "Enter a line to write to the file (type 'exit' to stop):" << std::endl;
            std::string inputLine;
            while (true) {
                std::getline(std::cin, inputLine);
                if (inputLine == "exit")
                    break;
                outputFile << inputLine << std::endl;
            }
            std::cout << "Data written to the file 'output.txt'." << std::endl;
            // Close the file
            outputFile.close();
        } 
        else {
            std::cerr << "Error opening the file for writing." << std::endl;
            return 1;
        }
        
        // Reading from a file
        std::ifstream inputFile("output.txt");
        if (inputFile.is_open()) {
            std::cout << "Contents of the file 'output.txt':" << std::endl;
            std::string line;
            while (std::getline(inputFile, line)) {
                std::cout << line << std::endl;
            }
            // Close the file
            inputFile.close();
        } 
        else {
            std::cerr << "Error opening the file for reading." << std::endl;
            return 1;
        }

        return 0;
    }
    
}