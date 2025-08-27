#include <iostream>
#include "Handleable.h"

bool Handleable::toContinue() {
    while (true) {
        char choice;
        std::cout << "\nChoice: ";
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            return true;
        }
        else if (choice == 'n' || choice == 'N') {
            return false;
        }
        else {
            std::cout << "Enter Valid Choice (Y || N):-\n";
        }
    }
}

int Handleable::handlingInt(std::string numberName) {
    int number = 0;
    while (true) {
        try {
            std::cin >> number;
            if (std::cin.fail()) {
                throw std::runtime_error("");
            }
            break;
        } catch (std::runtime_error e) {
            std::cout << "Enter Valid " << numberName << ": ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    return number;
}

int Handleable::handlingChoiceNotFound(int maxChoice) {
    while (true) {
        int choice = handlingInt("Choice");
        if (choice <= 0 || choice > maxChoice) {
            std::cout << "Enter Valid Choice: ";
        } else {
            return choice;
        }
    }
}

std::string Handleable::emptyString(std::string text, std::string message) {
    while (trim(text).empty()) {
        std::cout << "Enter Valid " << message << ": ";
        std::getline(std::cin, text);
    }
    return text;
}

std::string Handleable::handlingMinInputs(std::string value, int min) {
    if (value.length() < min) {
        std::cout << "Input Must Be " << min << " Characters At Least\n";
        return "";
    }
    return value;
}

std::string Handleable::handlingNumbers(std::string value, std::string message) {
    auto isValidNumber = [&]() {
        for (const auto& c : value) {
            if (c < '0' || c > '9') {
                std::cout << message << " Must Be Integer Digits Only!\nEnter Valid " << message << ": ";
                std::getline(std::cin, value);
                return false;
            }
        }
        if (handlingMinInputs(value).empty()) {
            std::getline(std::cin, value);
            return false;
        }
        return true;
    };

    do {
        value = emptyString(value, message);
    } while (!isValidNumber());
    return value;
}

std::string Handleable::trim(std::string value) {
    std::string result = "";
    for (const auto& c : value) {
        if (c != ' ')
            result += c;
    }
    return result;
}

std::string Handleable::toLowerCase(std::string value) {
    for (auto& c : value) {
        if (c >= 'A' && c <= 'Z') {
            c += 32;
            continue;
        }
    }
    return value;
}

std::string Handleable::toUpperCase(std::string value) {
    for (auto& c : value) {
        if (c >= 'a' && c <= 'z') {
            c -= 32;
            continue;
        }
    }
    return value;
}
