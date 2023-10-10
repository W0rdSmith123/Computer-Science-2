#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>

enum class Shift {
    DAY = 1,
    NIGHT = 2
};

class Date {
public:
    Date(int year, int month, int day) {
        if (year < 0) {
            throw std::invalid_argument("Year must be positive");
        }
        if (month < 1 || month > 12) {
            throw std::invalid_argument("Month must be between 1 and 12");
        }
        int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        bool is_leap_year = year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
        if (day < 1 || day > days_in_month[month - 1] || (month == 2 && day == 29 && !is_leap_year)) {
            throw std::invalid_argument("Day must be between 1 and the valid day for the month");
        }
        this->year = year;
        this->month = month;
        this->day = day;
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    std::string to_string() const {
        std::ostringstream oss;
        oss << year << "-" << month << "-" << day;
        return oss.str();
    }

private:
    int year;
    int month;
    int day;
};

class Cook {
public:
    Cook(const std::string& name, const Date& hire_date) : name(name), hire_date(hire_date) {}

    virtual ~Cook() {}

    Date getHireDate() const {
        return hire_date;
    }

    std::string getName() const {
        return name;
    }
    
protected:
    std::string name;
    Date hire_date;
};

class FastFoodCook : public Cook {
public:
    FastFoodCook(const std::string& name, const Date& hire_date, Shift shift)
        : Cook(name, hire_date), shift(shift) {}

    Shift getShift() const {
        return shift;
    }

private:
    Shift shift;
};

int main() {
    int num_cooks;
    std::cout << "Enter a number of fast food cooks: ";
    while (!(std::cin >> num_cooks)) {
        std::cout << "Invalid input. Try again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::vector<FastFoodCook> cooks;
    std::cin.ignore();
    for (int i = 0; i < num_cooks; ++i) {
        std::string name, hire_date_str;
        int shift_val, year, month, day;
        char dummy;

        std::cout << "Enter name of cook: ";
        std::getline(std::cin, name);

        std::cout << "Enter hire date of cook (YYYY-MM-DD): ";
        std::getline(std::cin, hire_date_str);
        std::istringstream iss(hire_date_str);
        if (!(iss >> year >> dummy >> month >> dummy >> day)) {
            std::cout << "Invalid date format. Try again." << std::endl;
            --i;
            continue;
        }

        std::cout << "Enter shift of cook (1 for day, 2 for night): ";
        if (!(std::cin >> shift_val) || (shift_val != 1 && shift_val != 2)) {
            std::cout << "Invalid shift. Try again." << std::endl;
            --i;
            continue;
        }

        cooks.push_back(FastFoodCook(name, Date(year, month, day), static_cast<Shift>(shift_val)));
        std::cin.ignore();
    }

    Date max_date(2019, 1, 1);
    std::cout << "Valid cooks:" << std::endl;
    for (const auto& cook : cooks) {
        if (cook.getShift() != Shift::DAY) {
            continue;
        }
        if (cook.getHireDate() < max_date) {
            std::cout << cook.getName() << std::endl;
        }
    }

}