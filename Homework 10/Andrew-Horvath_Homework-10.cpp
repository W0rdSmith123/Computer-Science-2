#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <limits>

// Function to check if a string is a palindrome, with options for case, punctuation, and space sensitivity.
bool is_palindrome(const std::string &s, bool case_sensitive, bool punctuation_sensitive, bool space_sensitive) {
    int left = 0, right = s.length() - 1;

    while (left < right) {
        if (!case_sensitive) {
            while (left < right && !std::isalnum(s[left])) ++left;
            while (left < right && !std::isalnum(s[right])) --right;
            if (std::tolower(s[left]) != std::tolower(s[right])) return false;
        } else {
            if (!punctuation_sensitive) {
                while (left < right && !std::isalnum(s[left])) ++left;
                while (left < right && !std::isalnum(s[right])) --right;
            }
            if (!space_sensitive) {
                while (left < right && s[left] == ' ') ++left;
                while (left < right && s[right] == ' ') --right;
            }
            if (s[left] != s[right]) return false;
        }
        ++left;
        --right;
    }
    return true;
}

// Function to safely get boolean input (0 or 1) from the user.
bool get_boolean_input(const std::string &prompt) {
    int choice;
    while (true) {
        std::cout << prompt;
        std::cin >> choice;

        if (std::cin.fail() || (choice != 0 && choice != 1)) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard the input
            std::cout << "Invalid input. Please enter 1 for yes or 0 for no.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard any extra input
            return choice == 1;
        }
    }
}

void check_palindrome(bool case_sensitive, bool punctuation_sensitive, bool space_sensitive) {
    std::string input;

    std::cout << "Enter a string to check for palindrome: ";
    std::getline(std::cin, input);

    bool result = is_palindrome(input, case_sensitive, punctuation_sensitive, space_sensitive);
    std::cout << "The string '" << input << "' is " << (result ? "" : "not ") << "a palindrome.\n";
}

void display_menu() {
    std::cout << "\nPalindrome Checker\n";
    std::cout << "1. Check a string\n";
    std::cout << "2. Options\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice (1-3): ";
}

int main() {
    bool case_sensitive = true;
    bool punctuation_sensitive = true;
    bool space_sensitive = true;

    while (true) {
        display_menu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard newline

        switch (choice) {
            case 1:
                check_palindrome(case_sensitive, punctuation_sensitive, space_sensitive);
                break;
            case 2:
                case_sensitive = get_boolean_input("Case sensitive (1-yes, 0-no): ");
                punctuation_sensitive = get_boolean_input("Punctuation sensitive (1-yes, 0-no): ");
                space_sensitive = get_boolean_input("Space sensitive (1-yes, 0-no): ");
                break;
            case 3:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                break;
        }
    }
}
