#include <iostream>


int main() {
    // if
    if (1) {
        int number;

        // Prompt the user to enter a number
        std::cout << "Enter an integer: ";
        std::cin >> number;

        // Check if the number is even or odd
        if (number % 2 == 0) {
            std::cout << number << " is an even number." << std::endl;
        } else {
            std::cout << number << " is an odd number." << std::endl;
        }
    }
    //switch statement
    if(0) {
        // Declare a variable to store the user input
        int dayNumber;
        std::cout << "Enter a number (1-7) to represent the day of the week: ";
        std::cin >> dayNumber;

        // Use a switch statement to determine the day of the week
        switch (dayNumber) {
            case 1:
                std::cout << "Monday" << std::endl;
                break;
            case 2:
                std::cout << "Tuesday" << std::endl;
                break;
            case 3:
                std::cout << "Wednesday" << std::endl;
                break;
            case 4:
                std::cout << "Thursday" << std::endl;
                break;
            case 5:
                std::cout << "Friday" << std::endl;
                break;
            case 6:
                std::cout << "Saturday" << std::endl;
                break;
            case 7:
                std::cout << "Sunday" << std::endl;
                break;
            default:
                std::cout << "Invalid input. Please enter a number between 1 and 7." << std::endl;
        }
    }   
    
    // for loop
    if (0) {
        // Declare variables
        int limit, sum = 0;

        // Prompt the user to enter a limit
        std::cout << "Enter a positive integer as the limit: ";
        std::cin >> limit;

        // Check if the entered limit is positive
        if (limit <= 0) {
            std::cout << "Please enter a positive integer." << std::endl;
            return 1; // Exit the program with an error code
        }

        // Use a for loop to calculate the sum of numbers from 1 to the limit
        for (int i = 1; i <= limit; ++i) {
            sum += i; // Add the current number to the sum
        }

        // Display the result
        std::cout << "The sum of numbers from 1 to " << limit << " is: " << sum << std::endl;
    }

    //while loop
    if (0) {

        // Declare variables
        int number, factorial = 1;

        // Prompt the user to enter a positive integer
        std::cout << "Enter a positive integer: ";
        std::cin >> number;

        // Check if the entered number is positive
        if (number < 0) {
            std::cout << "Please enter a positive integer." << std::endl;
            return 1; // Exit the program with an error code
        }

        // Use a while loop to calculate the factorial of the number
        int i = 1;
        while (i <= number) {
            factorial *= i; // Multiply the current number to the factorial
            ++i;           // Increment the loop variable
        }

        // Display the result
        std::cout << "The factorial of " << number << " is: " << factorial << std::endl;

    }

        
    return 0;
}