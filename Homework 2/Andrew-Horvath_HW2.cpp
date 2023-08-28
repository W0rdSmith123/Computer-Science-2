#include <iostream>
#include <vector>
#include <string>

int main() {
    struct Substance {
        std::string name;
        int freezingPoint;
        int boilingPoint;
    };

    std::vector<Substance> substances = {
        {"Ethyl alcohol", -173, 172},
        {"Mercury", -38, 676},
        {"Oxygen", -362, -306},
        {"Water", 32, 212}
    };

    int temperature;
    std::cout << "Enter a temperature in °F: ";
    std::cin >> temperature;

    std::vector<std::string> willFreeze, willBoil;

    for (const auto &substance : substances) {
        if (temperature <= substance.freezingPoint) {
            willFreeze.push_back(substance.name);
        }
        if (temperature >= substance.boilingPoint) {
            willBoil.push_back(substance.name);
        }
    }

    if (!willFreeze.empty()) {
        std::cout << "At " << temperature << "°F, the following substances will freeze: ";
        for (size_t i = 0; i < willFreeze.size(); ++i) {
            std::cout << willFreeze[i];
            if (i < willFreeze.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "." << std::endl;
    }

    if (!willBoil.empty()) {
        std::cout << "At " << temperature << "°F, the following substances will boil: ";
        for (size_t i = 0; i < willBoil.size(); ++i) {
            std::cout << willBoil[i];
            if (i < willBoil.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "." << std::endl;
    }

    if (willFreeze.empty() && willBoil.empty()) {
        std::cout << "At " << temperature << "°F, none of the listed substances will freeze or boil." << std::endl;
    }

    return 0;
}
