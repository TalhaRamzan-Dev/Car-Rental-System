#include "BookingUI.h"
#include <iostream>
#include <iomanip>

BookingUI::BookingUI() {
}

void BookingUI::showMainMenu() {
    Menu menu("Booking Management");
    
    menu.addOption("Add New Booking", [this]() { addBooking(); });
    menu.addOption("View All Bookings", [this]() { viewAllBookings(); });
    menu.addOption("View Booking by ID", [this]() { viewBookingById(); });
    menu.addOption("View Bookings by Customer", [this]() { viewBookingsByCustomer(); });
    menu.addOption("View Bookings by Car", [this]() { viewBookingsByCar(); });
    menu.addOption("Update Booking", [this]() { updateBooking(); });
    menu.addOption("Delete Booking", [this]() { deleteBooking(); });
    menu.addOption("View Active Bookings", [this]() { viewActiveBookings(); });
    
    menu.run();
}

void BookingUI::addBooking() {
    Menu::displayHeader("Add New Booking");
    
    Booking booking = createBookingFromInput();
    if (!booking.isValid()) {
        Menu::displayError("Invalid booking data: " + booking.getValidationErrors());
        Menu::pause();
        return;
    }
    
    if (bookingService.addBooking(booking)) {
        Menu::displaySuccess("Booking added successfully!");
    } else {
        Menu::displayError("Failed to add booking. Please try again.");
    }
    
    Menu::pause();
}

void BookingUI::viewAllBookings() {
    Menu::displayHeader("All Bookings");
    
    std::vector<Booking> bookings = bookingService.getAllBookings();
    if (bookings.empty()) {
        Menu::displayInfo("No bookings found.");
    } else {
        displayBookings(bookings);
    }
    
    Menu::pause();
}

void BookingUI::viewBookingById() {
    Menu::displayHeader("View Booking by ID");
    
    int bookingId = Menu::getPositiveInt("Enter Booking ID: ");
    Booking booking = bookingService.getBookingById(bookingId);
    
    if (booking.getBookingId() == 0) {
        Menu::displayError("Booking not found with ID: " + std::to_string(bookingId));
    } else {
        displayBooking(booking);
    }
    
    Menu::pause();
}

void BookingUI::viewBookingsByCustomer() {
    Menu::displayHeader("Bookings by Customer");
    
    int customerId = Menu::getPositiveInt("Enter Customer ID: ");
    std::vector<Booking> bookings = bookingService.getBookingsByCustomerId(customerId);
    
    if (bookings.empty()) {
        Menu::displayInfo("No bookings found for Customer ID: " + std::to_string(customerId));
    } else {
        displayBookings(bookings);
    }
    
    Menu::pause();
}

void BookingUI::viewBookingsByCar() {
    Menu::displayHeader("Bookings by Car");
    
    int carId = Menu::getPositiveInt("Enter Car ID: ");
    std::vector<Booking> bookings = bookingService.getBookingsByCarId(carId);
    
    if (bookings.empty()) {
        Menu::displayInfo("No bookings found for Car ID: " + std::to_string(carId));
    } else {
        displayBookings(bookings);
    }
    
    Menu::pause();
}

void BookingUI::updateBooking() {
    Menu::displayHeader("Update Booking");
    
    int bookingId = Menu::getPositiveInt("Enter Booking ID to update: ");
    Booking booking = bookingService.getBookingById(bookingId);
    
    if (booking.getBookingId() == 0) {
        Menu::displayError("Booking not found with ID: " + std::to_string(bookingId));
        Menu::pause();
        return;
    }
    
    displayBooking(booking);
    std::cout << "\nEnter new details:" << std::endl;
    updateBookingFromInput(booking);
    
    if (!booking.isValid()) {
        Menu::displayError("Invalid booking data: " + booking.getValidationErrors());
        Menu::pause();
        return;
    }
    
    if (bookingService.updateBooking(booking)) {
        Menu::displaySuccess("Booking updated successfully!");
    } else {
        Menu::displayError("Failed to update booking. Please try again.");
    }
    
    Menu::pause();
}

void BookingUI::deleteBooking() {
    Menu::displayHeader("Delete Booking");
    
    int bookingId = Menu::getPositiveInt("Enter Booking ID to delete: ");
    Booking booking = bookingService.getBookingById(bookingId);
    
    if (booking.getBookingId() == 0) {
        Menu::displayError("Booking not found with ID: " + std::to_string(bookingId));
        Menu::pause();
        return;
    }
    
    displayBooking(booking);
    
    if (Menu::getYesNo("Are you sure you want to delete this booking?")) {
        if (bookingService.deleteBooking(bookingId)) {
            Menu::displaySuccess("Booking deleted successfully!");
        } else {
            Menu::displayError("Failed to delete booking. Please try again.");
        }
    } else {
        Menu::displayInfo("Deletion cancelled.");
    }
    
    Menu::pause();
}

void BookingUI::viewActiveBookings() {
    Menu::displayHeader("Active Bookings");
    
    std::vector<Booking> allBookings = bookingService.getAllBookings();
    std::vector<Booking> activeBookings;
    
    for (const auto& booking : allBookings) {
        if (booking.isActive()) {
            activeBookings.push_back(booking);
        }
    }
    
    if (activeBookings.empty()) {
        Menu::displayInfo("No active bookings found.");
    } else {
        displayBookings(activeBookings);
    }
    
    Menu::pause();
}

void BookingUI::displayBooking(const Booking& booking) {
    booking.display();
}

void BookingUI::displayBookings(const std::vector<Booking>& bookings) {
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(8) << "CustID" 
              << std::setw(6) << "CarID" 
              << std::setw(12) << "Start Date" 
              << std::setw(12) << "End Date" 
              << std::setw(8) << "Days" 
              << std::setw(12) << "Total Cost" 
              << std::setw(10) << "Status" << std::endl;
    std::cout << std::string(90, '-') << std::endl;
    
    for (const auto& booking : bookings) {
        std::cout << std::left << std::setw(5) << booking.getBookingId()
                  << std::setw(8) << booking.getCustomerId()
                  << std::setw(6) << booking.getCarId()
                  << std::setw(12) << booking.getStartDate()
                  << std::setw(12) << booking.getEndDate()
                  << std::setw(8) << booking.getDuration()
                  << std::setw(12) << std::fixed << std::setprecision(2) << booking.getTotalCost()
                  << std::setw(10) << booking.getStatus()
                  << std::endl;
    }
}

Booking BookingUI::createBookingFromInput() {
    Booking booking;
    
    // Display available customers
    displayCustomerSelection();
    booking.setCustomerId(Menu::getPositiveInt("Enter Customer ID: "));
    
    // Display available cars
    displayCarSelection();
    booking.setCarId(Menu::getPositiveInt("Enter Car ID: "));
    
    booking.setStartDate(Menu::getNonEmptyString("Enter Start Date (YYYY-MM-DD): "));
    booking.setEndDate(Menu::getNonEmptyString("Enter End Date (YYYY-MM-DD): "));
    
    // Calculate total cost
    Car car = carService.getCarById(booking.getCarId());
    if (car.getCarId() > 0) {
        double totalCost = booking.calculateCost(car.getDailyRate());
        booking.setTotalCost(totalCost);
        std::cout << "Calculated total cost: $" << std::fixed << std::setprecision(2) << totalCost << std::endl;
    } else {
        booking.setTotalCost(Menu::getPositiveDouble("Enter Total Cost: $"));
    }
    
    booking.setStatus("Active");
    booking.setNotes(Menu::getString("Enter Notes (optional): "));
    
    return booking;
}

void BookingUI::updateBookingFromInput(Booking& booking) {
    std::string input;
    
    std::cout << "Customer ID [" << booking.getCustomerId() << "]: ";
    input = Menu::getString("Customer ID [" + std::to_string(booking.getCustomerId()) + "]: ");
    if (!input.empty()) booking.setCustomerId(std::stoi(input));
    
    std::cout << "Car ID [" << booking.getCarId() << "]: ";
    input = Menu::getString("Car ID [" + std::to_string(booking.getCarId()) + "]: ");
    if (!input.empty()) booking.setCarId(std::stoi(input));
    
    std::cout << "Start Date [" << booking.getStartDate() << "]: ";
    input = Menu::getString("Start Date [" + booking.getStartDate() + "]: ");
    if (!input.empty()) booking.setStartDate(input);
    
    std::cout << "End Date [" << booking.getEndDate() << "]: ";
    input = Menu::getString("End Date [" + booking.getEndDate() + "]: ");
    if (!input.empty()) booking.setEndDate(input);
    
    std::cout << "Status [" << booking.getStatus() << "]: ";
    input = Menu::getString("Status [" + booking.getStatus() + "]: ");
    if (!input.empty()) booking.setStatus(input);
    
    std::cout << "Notes [" << booking.getNotes() << "]: ";
    input = Menu::getString("Notes [" + booking.getNotes() + "]: ");
    if (!input.empty()) booking.setNotes(input);
}

void BookingUI::displayCarSelection() {
    std::vector<Car> cars = carService.getAvailableCars();
    if (cars.empty()) {
        Menu::displayInfo("No available cars found.");
        return;
    }
    
    std::cout << "\nAvailable Cars:" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(15) << "Make" 
              << std::setw(15) << "Model" 
              << std::setw(8) << "Year" 
              << std::setw(12) << "Daily Rate" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (const auto& car : cars) {
        std::cout << std::left << std::setw(5) << car.getCarId()
                  << std::setw(15) << car.getMake()
                  << std::setw(15) << car.getModel()
                  << std::setw(8) << car.getYear()
                  << std::setw(12) << std::fixed << std::setprecision(2) << car.getDailyRate()
                  << std::endl;
    }
}

void BookingUI::displayCustomerSelection() {
    std::vector<Customer> customers = customerService.getAllCustomers();
    if (customers.empty()) {
        Menu::displayInfo("No customers found.");
        return;
    }
    
    std::cout << "\nCustomers:" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(25) << "Email" 
              << std::setw(10) << "License" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    
    for (const auto& customer : customers) {
        std::cout << std::left << std::setw(5) << customer.getCustomerId()
                  << std::setw(20) << customer.getFullName()
                  << std::setw(25) << customer.getEmail()
                  << std::setw(10) << (customer.isLicenseValid() ? "Valid" : "Invalid")
                  << std::endl;
    }
}
