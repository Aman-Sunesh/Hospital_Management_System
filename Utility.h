#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <termios.h> // For terminal control functions
#include <unistd.h>  // For STDIN_FILENO

using namespace std;

// Declare the template function in the header file
template <typename T>
bool isInvalidInput(T& input) {
    if (!(std::cin >> input)) {
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cout << "Invalid input. Please try again.\n";
        return true;
    }
    return false;
}

// Inline specialization for std::string to prevent multiple definitions
template <>
inline bool isInvalidInput<string>(string& input) {
    getline(cin, input);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please try again.\n";
        return true;
    }
    return false; // Assume input is valid
}

// Function to read a single character without echoing
inline char getch() {
    char ch;
    struct termios oldt, newt;

    // Save current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable buffering and echoing
    newt.c_lflag &= ~(ICANON | ECHO);

    // Apply the new settings
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read a single character
    cin.get(ch);

    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

inline void clearScreen() {
    // ANSI escape code to clear screen
    cout << "\x1B[2J\x1B[H";
}

#endif // UTILITY_H
