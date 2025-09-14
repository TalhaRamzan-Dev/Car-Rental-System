#include <iostream>
#include <memory>
#include "database/FileManager.h"
#include "ui/Menu.h"
#include "ui/CarUI.h"
#include "ui/CustomerUI.h"
#include "ui/BookingUI.h"

class CarRentalSystem {
private:
    std::unique_ptr<CarUI> carUI;
    std::unique_ptr<CustomerUI> customerUI;
    std::unique_ptr<BookingUI> bookingUI;

public:
    CarRentalSystem() 
        : carUI(std::make_unique<CarUI>())
        , customerUI(std::make_unique<CustomerUI>())
        , bookingUI(std::make_unique<BookingUI>()) {
    }

    void run() {
        // Initialize file system
        if (!initializeFileSystem()) {
            std::cout << "Failed to initialize file system. Exiting..." << std::endl;
            Menu::pause();
            return;
        }

        // Show main menu
        showMainMenu();
    }

private:
    bool initializeFileSystem() {
        try {
            FileManager fileManager;
            
            if (!fileManager.initializeDataDirectory()) {
                std::cout << "Failed to initialize data directory." << std::endl;
                return false;
            }
            
            std::cout << "File system initialized successfully!" << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cout << "File system initialization error: " << e.what() << std::endl;
            return false;
        }
    }

    void showMainMenu() {
        Menu menu("Car Rental Management System");
        
        menu.addOption("Car Management", [this]() { carUI->showMainMenu(); });
        menu.addOption("Customer Management", [this]() { customerUI->showMainMenu(); });
        menu.addOption("Booking Management", [this]() { bookingUI->showMainMenu(); });
        menu.addOption("System Information", [this]() { showSystemInfo(); });
        menu.addOption("Exit", [this, &menu]() { menu.stop(); });
        
        menu.run();
    }

    void showSystemInfo() {
        Menu::displayHeader("System Information");
        
        std::cout << "=== Car Rental Management System ===" << std::endl;
        std::cout << "Version: 1.0.0 (Simplified)" << std::endl;
        std::cout << "Storage: File-based (CSV)" << std::endl;
        std::cout << "Features:" << std::endl;
        std::cout << "- Complete CRUD operations for Cars, Customers, and Bookings" << std::endl;
        std::cout << "- File-based data storage with CSV format" << std::endl;
        std::cout << "- Object-oriented design" << std::endl;
        std::cout << "- Simple and easy to use interface" << std::endl;
        std::cout << "- No external dependencies required" << std::endl;
        
        Menu::pause();
    }
};

int main() {
    try {
        std::cout << "Starting Car Rental Management System..." << std::endl;
        
        CarRentalSystem system;
        system.run();
        
        std::cout << "Thank you for using Car Rental Management System!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Fatal error: " << e.what() << std::endl;
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();
        return 1;
    }
}
