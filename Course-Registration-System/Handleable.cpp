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
    auto isEmpty = [](std::string text) {
        for (auto& c : text) {
            if (c != ' ')
                return false;
        }
        return true;
    };

    while (isEmpty(text)) {
        std::cout << "Enter Valid " << message << ": ";
        std::getline(std::cin, text);
    }

    return text;
}

std::string Handleable::handlingUsername(std::string username) {
    return std::string();
}