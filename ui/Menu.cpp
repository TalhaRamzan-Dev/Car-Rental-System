#include "Menu.h"
#include <limits>
#include <cstdlib>

Menu::Menu(const std::string& title) : title(title), isRunning(false) {
}

void Menu::addOption(const std::string& option, std::function<void()> action) {
    options.push_back(option);
    actions.push_back(action);
}

void Menu::display() const {
    clearScreen();
    displayHeader(title);
    
    for (size_t i = 0; i < options.size(); i++) {
        std::cout << (i + 1) << ". " << options[i] << std::endl;
    }
    std::cout << "0. Exit" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}

void Menu::run() {
    isRunning = true;
    
    while (isRunning) {
        display();
        int choice = getChoice(0, static_cast<int>(options.size()));
        
        if (choice == 0) {
            stop();
        } else if (choice > 0 && choice <= static_cast<int>(options.size())) {
            try {
                actions[choice - 1]();
            } catch (const std::exception& e) {
                displayError("An error occurred: " + std::string(e.what()));
                pause();
            }
        }
    }
}

void Menu::stop() {
    isRunning = false;
}

void Menu::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Menu::pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

int Menu::getChoice(int minChoice, int maxChoice) {
    int choice;
    while (true) {
        std::cout << "\nEnter your choice (" << minChoice << "-" << maxChoice << "): ";
        if (std::cin >> choice) {
            if (choice >= minChoice && choice <= maxChoice) {
                std::cin.ignore();
                return choice;
            } else {
                displayError("Invalid choice! Please enter a number between " + 
                           std::to_string(minChoice) + " and " + std::to_string(maxChoice) + ".");
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayError("Invalid input! Please enter a valid number.");
        }
    }
}

std::string Menu::getString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

std::string Menu::getNonEmptyString(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty()) {
            return input;
        }
        displayError("This field cannot be empty. Please try again.");
    }
}

int Menu::getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore();
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayError("Invalid input! Please enter a valid integer.");
        }
    }
}

int Menu::getPositiveInt(const std::string& prompt) {
    int value;
    while (true) {
        value = getInt(prompt);
        if (value > 0) {
            return value;
        }
        displayError("Please enter a positive integer.");
    }
}

double Menu::getDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore();
            return value;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayError("Invalid input! Please enter a valid number.");
        }
    }
}

double Menu::getPositiveDouble(const std::string& prompt) {
    double value;
    while (true) {
        value = getDouble(prompt);
        if (value > 0) {
            return value;
        }
        displayError("Please enter a positive number.");
    }
}

bool Menu::getYesNo(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::getline(std::cin, input);
        if (input == "y" || input == "Y" || input == "yes" || input == "YES") {
            return true;
        } else if (input == "n" || input == "N" || input == "no" || input == "NO") {
            return false;
        }
        displayError("Please enter 'y' for yes or 'n' for no.");
    }
}

void Menu::displayHeader(const std::string& title) {
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void Menu::displayError(const std::string& message) {
    std::cout << "\n[ERROR] " << message << std::endl;
}

void Menu::displaySuccess(const std::string& message) {
    std::cout << "\n[SUCCESS] " << message << std::endl;
}

void Menu::displayInfo(const std::string& message) {
    std::cout << "\n[INFO] " << message << std::endl;
}
