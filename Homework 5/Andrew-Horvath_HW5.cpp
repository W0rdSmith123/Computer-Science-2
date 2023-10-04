#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>

enum class EmployeeType
{
    MANAGER,
    ENGINEER,
    RESEARCHER
};

class Employee
{
protected:
    std::string mFirstName;
    std::string mLastName;
    std::string mTitle;
    int mSalary;

public:
    virtual ~Employee() {}
    virtual void InputData();
    virtual void SetData(const std::string &firstName, const std::string &lastName,
                         const std::string &title, int salary) = 0;
    virtual void SaveToFile(std::ofstream &out) = 0;
    virtual EmployeeType GetType() const = 0;
};

void Employee::InputData()
{
    std::cout << "Enter first name: ";
    std::cin >> mFirstName;
    std::cout << "Enter last name: ";
    std::cin >> mLastName;
    std::cout << "Enter title: ";
    std::cin >> mTitle;
    std::cout << "Enter salary: ";
    std::cin >> mSalary;
}

class Manager : public Employee
{
private:
    int mNumMeetingsPerWeek;
    int mNumVacationDaysPerYear;

public:
    void InputData() override
    {
        Employee::InputData();
        std::cout << "Enter number of meetings per week: ";
        std::cin >> mNumMeetingsPerWeek;
        std::cout << "Enter number of vacation days per year: ";
        std::cin >> mNumVacationDaysPerYear;
    }

    void SetData(const std::string &firstName, const std::string &lastName,
                 const std::string &title, int salary) override
    {
        mFirstName = firstName;
        mLastName = lastName;
        mTitle = title;
        mSalary = salary;
    }

    void SaveToFile(std::ofstream &out) override
    {
        out << "Manager " << mFirstName << " " << mLastName << " " << mTitle << " "
            << mSalary << " " << mNumMeetingsPerWeek << " " << mNumVacationDaysPerYear << "\n";
    }

    EmployeeType GetType() const override
    {
        return EmployeeType::MANAGER;
    }
};

class Engineer : public Employee
{
private:
    bool mKnowsCpp;
    int mYearsExperience;

public:
    void InputData() override
    {
        Employee::InputData();
        std::cout << "Do they know C++ (1 for yes, 0 for no): ";
        std::cin >> mKnowsCpp;
        std::cout << "Enter number of years of experience: ";
        std::cin >> mYearsExperience;
    }

    void SetData(const std::string &firstName, const std::string &lastName,
                 const std::string &title, int salary) override
    {
        mFirstName = firstName;
        mLastName = lastName;
        mTitle = title;
        mSalary = salary;
    }

    void SaveToFile(std::ofstream &out) override
    {
        out << "Engineer " << mFirstName << " " << mLastName << " " << mTitle << " "
            << mSalary << " " << mKnowsCpp << " " << mYearsExperience << "\n";
    }

    EmployeeType GetType() const override
    {
        return EmployeeType::ENGINEER;
    }
};

class Researcher : public Employee
{
private:
    std::string mPhDSchool;
    std::string mPhDTopic;

public:
    void InputData() override
    {
        Employee::InputData();
        std::cout << "Enter the school of their PhD: ";
        std::cin >> mPhDSchool;
        std::cout << "Enter the topic of their PhD Thesis: ";
        std::getline(std::cin, mPhDTopic);
    }

    void SetData(const std::string &firstName, const std::string &lastName,
                 const std::string &title, int salary) override
    {
        mFirstName = firstName;
        mLastName = lastName;
        mTitle = title;
        mSalary = salary;
    }

    void SaveToFile(std::ofstream &out) override
    {
        out << "Researcher " << mFirstName << " " << mLastName << " " << mTitle << " "
            << mSalary << " " << mPhDSchool << " " << mPhDTopic << "\n";
    }

    EmployeeType GetType() const override
    {
        return EmployeeType::RESEARCHER;
    }
};

void SaveToFile(std::vector<std::unique_ptr<Employee>> &aVector)
{
    std::ofstream outFile("employees.txt");
    if (!outFile)
    {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }

    for (const auto &emp : aVector)
    {
        emp->SaveToFile(outFile);
    }

    outFile.close();
}

void live()
{
    std::vector<std::unique_ptr<Employee>> employees;

    bool continueInput = true;
    while (continueInput)
    {
        std::cout << "Enter the type of employee (1: Manager, 2: Engineer, 3: Researcher) or 0 to finish: ";
        int choice;
        std::cin >> choice;

        if (choice == 0)
        {
            continueInput = false;
            continue;
        }

        std::unique_ptr<Employee> emp;

        switch (choice)
        {
        case 1:
            emp = std::make_unique<Manager>();
            break;
        case 2:
            emp = std::make_unique<Engineer>();
            break;
        case 3:
            emp = std::make_unique<Researcher>();
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            continue; // skip to next iteration
        }

        emp->InputData();
        employees.push_back(std::move(emp));

        std::cout << "Employee added successfully!\n";
    }

    SaveToFile(employees);
    std::cout << "Data saved to employees.txt\n";
}

void test()
{
    std::vector<std::unique_ptr<Employee>> employees;

    // Adding Manager data
    auto manager = std::make_unique<Manager>();
    manager->SetData("John", "Doe", "Manager", 100000);
    employees.push_back(std::move(manager));

    // Adding Engineer data
    auto engineer = std::make_unique<Engineer>();
    engineer->SetData("Jane", "Smith", "Software Engineer", 90000);
    employees.push_back(std::move(engineer));

    // Adding Researcher data
    auto researcher = std::make_unique<Researcher>();
    researcher->SetData("Alice", "Johnson", "Researcher", 80000);
    employees.push_back(std::move(researcher));

    SaveToFile(employees);
    std::cout << "Test data saved to employees.txt\n";
}

int main()
{
    // live();
    test();
    return 0;
}
