#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class Stack {
private:
    std::vector<int> items;

public:
    void push(int value) {
        if (std::find(items.begin(), items.end(), value) == items.end()) {
            items.push_back(value);
        } else {
            std::cout << "Value already exists in the stack.\n";
        }
    }

    void pop() {
        if (!items.empty()) {
            items.pop_back();
        } else {
            std::cout << "Stack is empty.\n";
        }
    }

    int size() const {
        return items.size();
    }

    int minItem() const {
        if (items.empty()) return -1;
        return *std::min_element(items.begin(), items.end());
    }

    int maxItem() const {
        if (items.empty()) return -1;
        return *std::max_element(items.begin(), items.end());
    }

    int findPosition(int value) const {
        auto it = std::find(items.begin(), items.end(), value);
        if (it == items.end()) return -1;
        return std::distance(items.begin(), it);
    }

    void printAll() const {
        for (int item : items) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
};

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add item\n";
    std::cout << "2. Delete item\n";
    std::cout << "3. Show item count\n";
    std::cout << "4. Show min and max items\n";
    std::cout << "5. Find the position of an item\n";
    std::cout << "6. Print all items\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int getValidInput() {
    int value;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input! Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return value;
}

int main() {
    Stack s;
    int choice, value;

    do {
        displayMenu();
        choice = getValidInput();

        switch (choice) {
            case 1:
                std::cout << "Enter value to add: ";
                value = getValidInput();
                s.push(value);
                break;
            case 2:
                s.pop();
                break;
            case 3:
                std::cout << "Item count: " << s.size() << "\n";
                break;
            case 4:
                std::cout << "Min item: " << s.minItem() << ", Max item: " << s.maxItem() << "\n";
                break;
            case 5:
                std::cout << "Enter value to find its position: ";
                value = getValidInput();
                int pos;
                pos = s.findPosition(value);
                if (pos != -1) {
                    std::cout << "Position of " << value << " is: " << pos << "\n";
                } else {
                    std::cout << "Item not found in the stack.\n";
                }
                break;
            case 6:
                std::cout << "All items: ";
                s.printAll();
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice! Please choose from the menu.\n";
        }
    } while (choice != 0);

    return 0;
}
