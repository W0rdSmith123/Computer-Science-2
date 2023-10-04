#include <iostream>
#include <stdexcept>
#include <string>
#include <ctime>

// --- Date Class and Exception ---

class InvalidDate : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid date. Please ensure date is in format DD-MM-YYYY and is valid.";
    }
};

class Date {
private:
    int day;
    int month;
    int year;

    bool isValidDate(int d, int m, int y) {
        if (y > 9999 || y < 1800) return false;
        if (m < 1 || m > 12) return false;

        int maxD = 31;
        if (m == 2) {
            bool isLeap = (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
            maxD = (isLeap) ? 29 : 28;
        } else if (m == 4 || m == 6 || m == 9 || m == 11) {
            maxD = 30;
        }

        return d > 0 && d <= maxD;
    }

public:
    Date(int day, int month, int year) : day(day), month(month), year(year) {
        if (!isValidDate(day, month, year)) {
            throw InvalidDate();
        }
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    std::string display() const {
        return std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);
    }
};

// --- Employee Class and Exception ---

class InvalidEmployeeNumber : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid employee number. Must be between 0 and 9999 inclusive.";
    }
};

class Employee {
private:
    std::string name;
    int number;
    Date hireDate;

public:
    Employee(const std::string& name, int number, const Date& hireDate) 
        : name(name), number(number), hireDate(hireDate) {
        if (number < 0 || number > 9999) {
            throw InvalidEmployeeNumber();
        }
    }

    std::string getName() const { return name; }
    int getNumber() const { return number; }
    Date getHireDate() const { return hireDate; }

    void setName(const std::string& name) { this->name = name; }
    void setNumber(int number) {
        if (number < 0 || number > 9999) {
            throw InvalidEmployeeNumber();
        }
        this->number = number;
    }
};

// --- ProductionWorker Class and Exceptions ---

const double MINIMUM_WAGE = 0.0;

enum Shift { DAY = 1, NIGHT = 2 };

class InvalidShift : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid shift. Use day(1) or night(2).";
    }
};

class InvalidPayRate : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid pay rate. Must be greater than the minimum wage.";
    }
};

class ProductionWorker : public Employee {
private:
    Shift shift;
    double hourlyPayRate;

public:
    ProductionWorker(const std::string& name, int number, const Date& hireDate,
                     Shift shift, double hourlyPayRate)
        : Employee(name, number, hireDate), shift(shift), hourlyPayRate(hourlyPayRate) {
        if (hourlyPayRate < MINIMUM_WAGE) {
            throw InvalidPayRate();
        }
    }

    Shift getShift() const { return shift; }
    double getHourlyPayRate() const { return hourlyPayRate; }

    void setShift(Shift shift) {
        if (shift != DAY && shift != NIGHT) {
            throw InvalidShift();
        }
        this->shift = shift;
    }

    void setHourlyPayRate(double hourlyPayRate) {
        if (hourlyPayRate < MINIMUM_WAGE) {
            throw InvalidPayRate();
        }
        this->hourlyPayRate = hourlyPayRate;
    }
};

// --- Main Driver Function ---

int main() {
    try {
        Date hireDateJohn(4, 10, 2023);
        Employee emp("John", 1234, hireDateJohn);
        std::cout << "Employee created successfully!" << std::endl;

        Date hireDateJane(2, 10, 2023);
        ProductionWorker worker("Jane", 5678, hireDateJane, DAY, 12.5);
        std::cout << "Production worker created successfully!" << std::endl;

        // Uncomment to trigger Date exceptions
        // Date invalidDate(30, 2, 2023);
        
        // Uncomment to trigger Employee exceptions
        // Date validDate(29, 2, 2024);
        // Employee empError("Doe", 10000, validDate);

        // Uncomment to trigger ProductionWorker exceptions
        ProductionWorker workerError("Smith", 5678, hireDateJane, DAY, 11.0);
        workerError.setShift(Shift(3));
        workerError.setHourlyPayRate(9.0);
        

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
