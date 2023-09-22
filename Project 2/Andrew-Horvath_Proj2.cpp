#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class PersonData {
private:
    std::string lastName;
    std::string firstName;
    std::string address;
    std::string city;
    std::string state;
    std::string zip;
    std::string phone;

public:
    // Accessor functions
    std::string getLastName() const { return lastName; }
    std::string getFirstName() const { return firstName; }
    std::string getAddress() const { return address; }
    std::string getCity() const { return city; }
    std::string getState() const { return state; }
    std::string getZip() const { return zip; }
    std::string getPhone() const { return phone; }

    // Mutator functions
    void setLastName(const std::string &ln) { lastName = ln; }
    void setFirstName(const std::string &fn) { firstName = fn; }
    void setAddress(const std::string &add) { address = add; }
    void setCity(const std::string &c) { city = c; }
    void setState(const std::string &st) { state = st; }
    void setZip(const std::string &z) { zip = z; }
    void setPhone(const std::string &ph) { phone = ph; }
};

class CustomerData : public PersonData {
private:
    int customerNumber;
    bool mailingList;
    static int nextCustomerNumber; // static member variable for uniqueness

public:
    CustomerData() {
        customerNumber = nextCustomerNumber++;
        mailingList = false;
    }

    // Accessor functions
    int getCustomerNumber() const { return customerNumber; }
    bool getMailingList() const { return mailingList; }

    // Mutator functions
    void setMailingList(bool ml) { mailingList = ml; }
};

// Initialize the static member variable
int CustomerData::nextCustomerNumber = 1;

// Custom getline function that removes '\r' character
std::istream& safeGetline(std::istream& is, std::string& line) {
    char ch;
    line.clear();

    while (is.get(ch) && ch != '\n') {
        if (ch != '\r') {
            line.push_back(ch);
        }
    }

    return is;
}

int main() {
    std::vector<CustomerData> customers;
    std::ifstream file("CustomerInfo.txt");

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (safeGetline(file, line)) {
        CustomerData customer;

        // Setting data for the customer
        customer.setLastName(line);
        safeGetline(file, line);
        customer.setFirstName(line);
        safeGetline(file, line);
        customer.setAddress(line);
        safeGetline(file, line);
        customer.setCity(line);
        safeGetline(file, line);
        customer.setState(line);
        safeGetline(file, line);
        customer.setZip(line);
        safeGetline(file, line);
        customer.setPhone(line);
        safeGetline(file, line);
        customer.setMailingList(line == "true");

        // Add the customer to the list
        customers.push_back(customer);

        // Skip the blank line
        safeGetline(file, line);
    }

    // Printing the customers who wish to be on the mailing list
    for (const CustomerData& customer : customers) {
        if (customer.getMailingList()) {
            std::cout << "Customer Number: " << customer.getCustomerNumber() << std::endl;
            std::cout << "Name: " << customer.getFirstName() << " " << customer.getLastName() << std::endl;
            std::cout << "Address: " << customer.getAddress() << ", " << customer.getCity() << ", " << customer.getState() << " " << customer.getZip() << std::endl;
            std::cout << "Phone: " << customer.getPhone() << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }

    return 0;
}
