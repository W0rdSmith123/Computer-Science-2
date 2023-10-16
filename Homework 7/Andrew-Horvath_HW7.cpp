#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>

const std::string DATA_FILENAME = "GasPrices.txt";
const std::string LOW_TO_HIGH_FILENAME = "LowToHigh.txt";
const std::string HIGH_TO_LOW_FILENAME = "HighToLow.txt";

struct GasPrice {
    int year;
    int month;
    int day;
    double price;
};

bool readData(std::vector<GasPrice>& prices) {
    std::ifstream file(DATA_FILENAME);
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        GasPrice entry;
        if(sscanf(line.c_str(), "%d-%d-%d:%lf", &entry.month, &entry.day, &entry.year, &entry.price) != 4) {
            std::cerr << "Error reading data from file." << std::endl;
            return false;
        }
        prices.push_back(entry);
    }
    file.close();
    return true;
}

bool isValidYear(const std::vector<GasPrice>& prices, int year) {
    std::set<int> validYears;
    for(const auto& price : prices) {
        validYears.insert(price.year);
    }
    return validYears.find(year) != validYears.end();
}

double averagePricePerYear(const std::vector<GasPrice>& prices, int year) {
    double sum = 0.0;
    int count = 0;
    for (const auto& price : prices) {
        if (price.year == year) {
            sum += price.price;
            count++;
        }
    }
    return (count == 0) ? 0 : sum / count;
}

double averagePricePerMonth(const std::vector<GasPrice>& prices, int year, int month) {
    double sum = 0.0;
    int count = 0;
    for (const auto& price : prices) {
        if (price.year == year && price.month == month) {
            sum += price.price;
            count++;
        }
    }
    return (count == 0) ? 0 : sum / count;
}

std::pair<double, double> highLowPricesPerYear(const std::vector<GasPrice>& prices, int year) {
    double highest = -1.0, lowest = 1e9;
    for (const auto& price : prices) {
        if (price.year == year) {
            if (price.price > highest) highest = price.price;
            if (price.price < lowest) lowest = price.price;
        }
    }
    return {highest, lowest};
}

bool savePricesToFile(const std::vector<GasPrice>& prices, const std::string& filename, bool ascending = true) {
    std::vector<double> allPrices;
    for (const auto& price : prices) {
        allPrices.push_back(price.price);
    }

    if (ascending) {
        std::sort(allPrices.begin(), allPrices.end());
    } else {
        std::sort(allPrices.rbegin(), allPrices.rend());
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error writing to file " << filename << std::endl;
        return false;
    }
    for (const auto& price : allPrices) {
        outFile << price << "\n";
    }
    outFile.close();
    return true;
}

int main() {
    std::vector<GasPrice> prices;
    if(!readData(prices)) {
        return 1; // Exit if there's an error reading data
    }

    int choice;
    while (true) {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1. Average price per year" << std::endl;
        std::cout << "2. Average Price per month" << std::endl;
        std::cout << "3. Highest and lowest price per year" << std::endl;
        std::cout << "4. List of prices lowest to highest (stored in a txt file)" << std::endl;
        std::cout << "5. List of prices highest to lowest (stored in a txt file)" << std::endl;
        std::cout << "6. Exit" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch(choice) {
            case 1: {
                int year;
                std::cout << "Enter year: ";
                std::cin >> year;
                if(isValidYear(prices, year)) {
                    std::cout << "Average price for " << year << ": $" << std::fixed << std::setprecision(2) << averagePricePerYear(prices, year) << std::endl;
                } else {
                    std::cerr << "Invalid year entered. Please try again." << std::endl;
                }
                break;
            }
            case 2: {
                int year, month;
                std::cout << "Enter year and month: ";
                std::cin >> year >> month;
                if(isValidYear(prices, year)) {
                    std::cout << "Average price for " << month << "/" << year << ": $" << std::fixed << std::setprecision(2) << averagePricePerMonth(prices, year, month) << std::endl;
                } else {
                    std::cerr << "Invalid year entered. Please try again." << std::endl;
                }
                break;
            }
            case 3: {
                int year;
                std::cout << "Enter year: ";
                std::cin >> year;
                if(isValidYear(prices, year)) {
                    auto [high, low] = highLowPricesPerYear(prices, year);
                    std::cout << "Highest price for " << year << ": $" << std::fixed << std::setprecision(2) << high << std::endl;
                    std::cout << "Lowest price for " << year << ": $" << std::fixed << std::setprecision(2) << low << std::endl;
                } else {
                    std::cerr << "Invalid year entered. Please try again." << std::endl;
                }
                break;
            }
            case 4: {
                if(savePricesToFile(prices, LOW_TO_HIGH_FILENAME, true)) {
                    std::cout << "Prices saved to " << LOW_TO_HIGH_FILENAME << std::endl;
                }
                break;
            }
            case 5: {
                if(savePricesToFile(prices, HIGH_TO_LOW_FILENAME, false)) {
                    std::cout << "Prices saved to " << HIGH_TO_LOW_FILENAME << std::endl;
                }
                break;
            }
            case 6:
                return 0;
            default:
                std::cout << "Invalid choice. Try again." << std::endl;
        }
    }
}
