#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>
#include <regex>
#include <climits>

int ComputeFib(int n, std::unordered_map<int, int>& memo, int& computationCount) {
    computationCount++;

    if (n <= 1) {
        return n;
    }

    if (memo.find(n) != memo.end()) {
        return memo[n];
    }

    auto prev = ComputeFib(n - 1, memo, computationCount);
    if (prev == -1) {
        memo[n] = -1;
        return -1;
    }

    auto prevPrev = ComputeFib(n - 2, memo, computationCount);
    if (prevPrev == -1) {
        memo[n] = -1;
        return -1;
    }

    // Check for overflow
    if (prev > INT_MAX - prevPrev) {
        memo[n] = -1; // Store overflow condition
        return -1; // Indicate an error or overflow
    }


    memo[n] = prev + prevPrev;
    return memo[n];
}

bool IsValidInput(const std::string& input) {
    return std::regex_match(input, std::regex("[0-9]+"));
}

int main() {
    std::unordered_map<int, int> memo;
    std::string input;

    while (true) {
        std::cout << "\nEnter a non-negative integer (or 'exit' to quit): ";
        std::cin >> input;

        if (input == "exit") {
            break;
        }

        if (!IsValidInput(input)) {
            std::cout << "Invalid input. Please enter a valid non-negative integer.\n";
            continue;
        }

        int n = std::stoi(input);
        int computationCount = 0;
        auto result = ComputeFib(n, memo, computationCount);

        if (result == -1) {
            std::cout << "Result is too large for 'int' type or an overflow occurred." << std::endl;
        } else {
            std::cout << "Fibonacci(" << n << ") = " << result;
            std::cout << " (Computed in " << computationCount << " calculations)" << std::endl;
        }
    }

    std::cout << "Exiting program.\n";
    return 0;
}
