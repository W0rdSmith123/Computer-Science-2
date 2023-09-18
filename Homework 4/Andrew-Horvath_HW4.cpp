#include <iostream>
#include <string>  // for std::string

class Employee {
private:
    std::string name;
    int number;
    std::string hireDate;

public:
    // Constructors
    Employee() : name(""), number(0), hireDate("") {}
    
    Employee(const std::string &n, int num, const std::string &date) 
        : name(n), number(num), hireDate(date) {  // Moved to initializer list
        setName(n);
        setNumber(num);
        setHireDate(date);
    }

    // Accessors (getters)
    std::string getName() const { return name; }
    int getNumber() const { return number; }
    std::string getHireDate() const { return hireDate; }

    // Mutators (setters)
    void setName(const std::string &n) {
        if (!n.empty()) {
            name = n;
        } else {
            std::cerr << "Error: Invalid name provided." << std::endl;
        }
    }

    void setNumber(int num) {
        if (num > 0) {
            number = num;
        } else {
            std::cerr << "Error: Invalid employee number provided." << std::endl;
        }
    }

    void setHireDate(const std::string &date) {
        if (date.size() == 10 && date[2] == '/' && date[5] == '/') {
            hireDate = date;
        } else {
            std::cerr << "Error: Invalid hire date format provided. Expected format: DD/MM/YYYY." << std::endl;
        }
    }
};

class ProductionWorker : public Employee {
private:
    int shift;         // 1 for day shift, 2 for night shift
    double hourlyRate;

public:
    // Constructors
    ProductionWorker() : Employee(), shift(1), hourlyRate(0.0) {}
    
    ProductionWorker(const std::string &n, int num, const std::string &date, int s, double rate) 
        : Employee(n, num, date), shift(s), hourlyRate(rate) {
        setShift(s);
        setHourlyRate(rate);
    }

    // Accessors (getters)
    int getShift() const { return shift; }
    double getHourlyRate() const { return hourlyRate; }

    // Mutators (setters)
    void setShift(int s) {
        if (s == 1 || s == 2) {
            shift = s;
        } else {
            std::cerr << "Error: Invalid shift provided. Acceptable values are 1 (Day) or 2 (Night)." << std::endl;
        }
    }

    void setHourlyRate(double rate) {
        if (rate >= 0) {
            hourlyRate = rate;
        } else {
            std::cerr << "Error: Negative hourly rate provided." << std::endl;
        }
    }
};

int main() {
    ProductionWorker worker("John Doe", 12345, "18/09/2023", 2, 20.50);

    std::cout << "Employee Name: " << worker.getName() << std::endl;
    std::cout << "Employee Number: " << worker.getNumber() << std::endl;
    std::cout << "Hire Date: " << worker.getHireDate() << std::endl;
    std::cout << "Shift: " << (worker.getShift() == 1 ? "Day" : "Night") << std::endl;
    std::cout << "Hourly Rate: $" << worker.getHourlyRate() << std::endl;

    return 0;
}
