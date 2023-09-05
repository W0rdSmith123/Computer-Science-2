#include <iostream>
#include <string>
#include <algorithm>

class StudentClass {
private:
    std::string mName;

public:
    // Overloaded Constructor
    StudentClass(const std::string &name = "") : mName(name) {}

    // Operator =
    StudentClass& operator=(const StudentClass &other) {
        if (this != &other) {
            mName = other.mName;
        }
        return *this;
    }

    // Operator +
    StudentClass& operator+(const StudentClass &other) {
        mName += " " + other.mName;
        return *this;
    }

    // Operator []
    char operator[](size_t index) const {
        if (index < mName.size()) {
            return mName[index];
        }
        throw std::out_of_range("Index out of range");
    }

    // Operator >>
    friend std::istream& operator>>(std::istream &input, StudentClass &student) {
        std::getline(input, student.mName);
        return input;
    }

    // Operator <<
    friend std::ostream& operator<<(std::ostream &output, const StudentClass &student) {
        output << student.mName;
        return output;
    }

    // CountLetters
    int CountLetters(char ch) const {
        return std::count(mName.begin(), mName.end(), ch);
    }

    // Reverse
    void Reverse() {
        std::reverse(mName.begin(), mName.end());
    }
};

int main() {
    StudentClass student1("John"), student2("Doe");
    std::cout << student1 << std::endl;
    std::cout << student2 << std::endl;

    student1 + student2;
    std::cout << student1 << std::endl;

    std::cout << "Letter 'o' appears " << student1.CountLetters('o') << " times." << std::endl;

    student1.Reverse();
    std::cout << "Reversed: " << student1 << std::endl;

    std::cout << "Enter a name: ";
    std::cin >> student2;
    std::cout << "You entered: " << student2 << std::endl;

    return 0;
}
