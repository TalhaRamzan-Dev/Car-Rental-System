#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Menu {
private:
    std::string title;
    std::vector<std::string> options;
    std::vector<std::function<void()>> actions;
    bool isRunning;

public:
    Menu(const std::string& title);
    
    void addOption(const std::string& option, std::function<void()> action);
    void display() const;
    void run();
    void stop();
    
    // Simple input methods
    static void clearScreen();
    static void pause();
    static int getChoice(int minChoice = 1, int maxChoice = 10);
    static std::string getString(const std::string& prompt);
    static std::string getNonEmptyString(const std::string& prompt);
    static int getInt(const std::string& prompt);
    static int getPositiveInt(const std::string& prompt);
    static double getDouble(const std::string& prompt);
    static double getPositiveDouble(const std::string& prompt);
    static bool getYesNo(const std::string& prompt);
    
    // Display helpers
    static void displayHeader(const std::string& title);
    static void displayError(const std::string& message);
    static void displaySuccess(const std::string& message);
    static void displayInfo(const std::string& message);
};

#endif // MENU_H
