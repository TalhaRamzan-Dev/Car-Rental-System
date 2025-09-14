#include "CarUI.h"
#include <iostream>
#include <iomanip>

CarUI::CarUI() {
}

void CarUI::showMainMenu() {
    Menu menu("Car Management");
    
    menu.addOption("Add New Car", [this]() { addCar(); });
    menu.addOption("View All Cars", [this]() { viewAllCars(); });
    menu.addOption("View Car by ID", [this]() { viewCarById(); });
    menu.addOption("Search Cars", [this]() { searchCars(); });
    menu.addOption("Update Car", [this]() { updateCar(); });
    menu.addOption("Delete Car", [this]() { deleteCar(); });
    menu.addOption("View Available Cars", [this]() { viewAvailableCars(); });
    menu.addOption("View Statistics", [this]() { viewStatistics(); });
    
    menu.run();
}

void CarUI::addCar() {
    Menu::displayHeader("Add New Car");
    
    Car car = createCarFromInput();
    if (!car.isValid()) {
        Menu::displayError("Invalid car data: " + car.getValidationErrors());
        Menu::pause();
        return;
    }
    
    if (carService.addCar(car)) {
        Menu::displaySuccess("Car added successfully!");
    } else {
        Menu::displayError("Failed to add car. Please try again.");
    }
    
    Menu::pause();
}

void CarUI::viewAllCars() {
    Menu::displayHeader("All Cars");
    
    std::vector<Car> cars = carService.getAllCars();
    if (cars.empty()) {
        Menu::displayInfo("No cars found.");
    } else {
        displayCars(cars);
    }
    
    Menu::pause();
}

void CarUI::viewCarById() {
    Menu::displayHeader("View Car by ID");
    
    int carId = Menu::getPositiveInt("Enter Car ID: ");
    Car car = carService.getCarById(carId);
    
    if (car.getCarId() == 0) {
        Menu::displayError("Car not found with ID: " + std::to_string(carId));
    } else {
        displayCar(car);
    }
    
    Menu::pause();
}

void CarUI::searchCars() {
    Menu::displayHeader("Search Cars");
    
    std::string searchTerm = Menu::getNonEmptyString("Enter search term: ");
    std::vector<Car> results = carService.searchCars(searchTerm);
    
    if (results.empty()) {
        Menu::displayInfo("No cars found matching: " + searchTerm);
    } else {
        std::cout << "Found " << results.size() << " car(s) matching: " << searchTerm << std::endl;
        displayCars(results);
    }
    
    Menu::pause();
}

void CarUI::updateCar() {
    Menu::displayHeader("Update Car");
    
    int carId = Menu::getPositiveInt("Enter Car ID to update: ");
    Car car = carService.getCarById(carId);
    
    if (car.getCarId() == 0) {
        Menu::displayError("Car not found with ID: " + std::to_string(carId));
        Menu::pause();
        return;
    }
    
    displayCar(car);
    std::cout << "\nEnter new details:" << std::endl;
    updateCarFromInput(car);
    
    if (!car.isValid()) {
        Menu::displayError("Invalid car data: " + car.getValidationErrors());
        Menu::pause();
        return;
    }
    
    if (carService.updateCar(car)) {
        Menu::displaySuccess("Car updated successfully!");
    } else {
        Menu::displayError("Failed to update car. Please try again.");
    }
    
    Menu::pause();
}

void CarUI::deleteCar() {
    Menu::displayHeader("Delete Car");
    
    int carId = Menu::getPositiveInt("Enter Car ID to delete: ");
    Car car = carService.getCarById(carId);
    
    if (car.getCarId() == 0) {
        Menu::displayError("Car not found with ID: " + std::to_string(carId));
        Menu::pause();
        return;
    }
    
    displayCar(car);
    
    if (Menu::getYesNo("Are you sure you want to delete this car?")) {
        if (carService.deleteCar(carId)) {
            Menu::displaySuccess("Car deleted successfully!");
        } else {
            Menu::displayError("Failed to delete car. Please try again.");
        }
    } else {
        Menu::displayInfo("Deletion cancelled.");
    }
    
    Menu::pause();
}

void CarUI::viewAvailableCars() {
    Menu::displayHeader("Available Cars");
    
    std::vector<Car> cars = carService.getAvailableCars();
    if (cars.empty()) {
        Menu::displayInfo("No available cars found.");
    } else {
        displayCars(cars);
    }
    
    Menu::pause();
}

void CarUI::viewStatistics() {
    Menu::displayHeader("Car Statistics");
    
    std::cout << "Total Cars: " << carService.getTotalCars() << std::endl;
    std::cout << "Available Cars: " << carService.getAvailableCarsCount() << std::endl;
    std::cout << "Rented Cars: " << carService.getRentedCarsCount() << std::endl;
    std::cout << "Maintenance Cars: " << carService.getMaintenanceCarsCount() << std::endl;
    std::cout << "Average Daily Rate: $" << std::fixed << std::setprecision(2) 
              << carService.getAverageDailyRate() << std::endl;
    
    Menu::pause();
}

void CarUI::displayCar(const Car& car) {
    car.display();
}

void CarUI::displayCars(const std::vector<Car>& cars) {
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(15) << "Make" 
              << std::setw(15) << "Model" 
              << std::setw(8) << "Year" 
              << std::setw(10) << "Status" 
              << std::setw(12) << "Daily Rate" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& car : cars) {
        std::cout << std::left << std::setw(5) << car.getCarId()
                  << std::setw(15) << car.getMake()
                  << std::setw(15) << car.getModel()
                  << std::setw(8) << car.getYear()
                  << std::setw(10) << car.getStatusString()
                  << std::setw(12) << std::fixed << std::setprecision(2) << car.getDailyRate()
                  << std::endl;
    }
}

Car CarUI::createCarFromInput() {
    Car car;
    
    car.setMake(Menu::getNonEmptyString("Enter Make: "));
    car.setModel(Menu::getNonEmptyString("Enter Model: "));
    car.setYear(Menu::getPositiveInt("Enter Year: "));
    car.setColor(Menu::getNonEmptyString("Enter Color: "));
    car.setLicensePlate(Menu::getNonEmptyString("Enter License Plate: "));
    car.setDailyRate(Menu::getPositiveDouble("Enter Daily Rate: $"));
    car.setMileage(Menu::getPositiveInt("Enter Mileage: "));
    car.setSeats(Menu::getPositiveInt("Enter Number of Seats: "));
    
    // Fuel Type
    std::cout << "Fuel Type (1-Gasoline, 2-Diesel, 3-Electric, 4-Hybrid): ";
    int fuelChoice = Menu::getChoice(1, 4);
    car.setFuelType(static_cast<FuelType>(fuelChoice - 1));
    
    // Transmission
    std::cout << "Transmission (1-Manual, 2-Automatic): ";
    int transChoice = Menu::getChoice(1, 2);
    car.setTransmission(static_cast<Transmission>(transChoice - 1));
    
    return car;
}

void CarUI::updateCarFromInput(Car& car) {
    std::string input;
    
    std::cout << "Make [" << car.getMake() << "]: ";
    input = Menu::getString("Make [" + car.getMake() + "]: ");
    if (!input.empty()) car.setMake(input);
    
    std::cout << "Model [" << car.getModel() << "]: ";
    input = Menu::getString("Model [" + car.getModel() + "]: ");
    if (!input.empty()) car.setModel(input);
    
    std::cout << "Year [" << car.getYear() << "]: ";
    input = Menu::getString("Year [" + std::to_string(car.getYear()) + "]: ");
    if (!input.empty()) car.setYear(std::stoi(input));
    
    std::cout << "Color [" << car.getColor() << "]: ";
    input = Menu::getString("Color [" + car.getColor() + "]: ");
    if (!input.empty()) car.setColor(input);
    
    std::cout << "License Plate [" << car.getLicensePlate() << "]: ";
    input = Menu::getString("License Plate [" + car.getLicensePlate() + "]: ");
    if (!input.empty()) car.setLicensePlate(input);
    
    std::cout << "Daily Rate [" << car.getDailyRate() << "]: ";
    input = Menu::getString("Daily Rate [" + std::to_string(car.getDailyRate()) + "]: ");
    if (!input.empty()) car.setDailyRate(std::stod(input));
    
    std::cout << "Mileage [" << car.getMileage() << "]: ";
    input = Menu::getString("Mileage [" + std::to_string(car.getMileage()) + "]: ");
    if (!input.empty()) car.setMileage(std::stoi(input));
    
    std::cout << "Seats [" << car.getSeats() << "]: ";
    input = Menu::getString("Seats [" + std::to_string(car.getSeats()) + "]: ");
    if (!input.empty()) car.setSeats(std::stoi(input));
}
