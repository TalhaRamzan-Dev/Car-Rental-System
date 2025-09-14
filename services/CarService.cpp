#include "CarService.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

CarService::CarService() : dataFile("data/cars.csv"), nextId(1) {
    loadCars(); // Load existing cars to get the correct next ID
}

bool CarService::addCar(const Car& car) {
    std::vector<Car> cars = loadCars();
    
    // Set the ID for the new car
    Car newCar = car;
    newCar.setCarId(getNextId());
    
    cars.push_back(newCar);
    nextId++;
    
    return saveCars(cars);
}

std::vector<Car> CarService::getAllCars() {
    return loadCars();
}

Car CarService::getCarById(int carId) {
    std::vector<Car> cars = loadCars();
    for (const auto& car : cars) {
        if (car.getCarId() == carId) {
            return car;
        }
    }
    return Car(); // Return empty car if not found
}

std::vector<Car> CarService::searchCars(const std::string& searchTerm) {
    std::vector<Car> cars = loadCars();
    std::vector<Car> results;
    std::string lowerSearchTerm = searchTerm;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);
    
    for (const auto& car : cars) {
        std::string make = car.getMake();
        std::string model = car.getModel();
        std::string color = car.getColor();
        std::string licensePlate = car.getLicensePlate();
        
        std::transform(make.begin(), make.end(), make.begin(), ::tolower);
        std::transform(model.begin(), model.end(), model.begin(), ::tolower);
        std::transform(color.begin(), color.end(), color.begin(), ::tolower);
        std::transform(licensePlate.begin(), licensePlate.end(), licensePlate.begin(), ::tolower);
        
        if (make.find(lowerSearchTerm) != std::string::npos ||
            model.find(lowerSearchTerm) != std::string::npos ||
            color.find(lowerSearchTerm) != std::string::npos ||
            licensePlate.find(lowerSearchTerm) != std::string::npos) {
            results.push_back(car);
        }
    }
    
    return results;
}

std::vector<Car> CarService::getAvailableCars() {
    std::vector<Car> cars = loadCars();
    std::vector<Car> availableCars;
    
    for (const auto& car : cars) {
        if (car.isAvailable()) {
            availableCars.push_back(car);
        }
    }
    
    return availableCars;
}

bool CarService::updateCar(const Car& car) {
    std::vector<Car> cars = loadCars();
    
    for (auto& c : cars) {
        if (c.getCarId() == car.getCarId()) {
            c = car;
            return saveCars(cars);
        }
    }
    
    return false; // Car not found
}

bool CarService::deleteCar(int carId) {
    std::vector<Car> cars = loadCars();
    
    auto it = std::remove_if(cars.begin(), cars.end(),
        [carId](const Car& car) { return car.getCarId() == carId; });
    
    if (it != cars.end()) {
        cars.erase(it, cars.end());
        return saveCars(cars);
    }
    
    return false; // Car not found
}

bool CarService::saveCars(const std::vector<Car>& cars) {
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        return false;
    }
    
    // Write header
    file << "ID,Make,Model,Year,Color,LicensePlate,DailyRate,Status,Mileage,FuelType,Transmission,Seats\n";
    
    // Write data
    for (const auto& car : cars) {
        file << carToCsvLine(car) << "\n";
    }
    
    file.close();
    return true;
}

std::vector<Car> CarService::loadCars() {
    std::vector<Car> cars;
    std::ifstream file(dataFile);
    
    if (!file.is_open()) {
        return cars; // Return empty vector if file doesn't exist
    }
    
    std::string line;
    bool firstLine = true;
    
    while (std::getline(file, line)) {
        if (firstLine) {
            firstLine = false;
            continue; // Skip header
        }
        
        if (!line.empty()) {
            Car car = parseCarFromLine(line);
            if (car.getCarId() > 0) { // Valid car
                cars.push_back(car);
            }
        }
    }
    
    file.close();
    updateNextId(cars);
    return cars;
}

int CarService::getNextId() {
    return nextId;
}

void CarService::setNextId(int id) {
    nextId = id;
}

int CarService::getTotalCars() {
    return loadCars().size();
}

int CarService::getAvailableCarsCount() {
    return getAvailableCars().size();
}

int CarService::getRentedCarsCount() {
    std::vector<Car> cars = loadCars();
    int count = 0;
    for (const auto& car : cars) {
        if (car.getStatus() == CarStatus::RENTED) {
            count++;
        }
    }
    return count;
}

int CarService::getMaintenanceCarsCount() {
    std::vector<Car> cars = loadCars();
    int count = 0;
    for (const auto& car : cars) {
        if (car.getStatus() == CarStatus::MAINTENANCE) {
            count++;
        }
    }
    return count;
}

double CarService::getAverageDailyRate() {
    std::vector<Car> cars = loadCars();
    if (cars.empty()) return 0.0;
    
    double total = 0.0;
    for (const auto& car : cars) {
        total += car.getDailyRate();
    }
    
    return total / cars.size();
}

Car CarService::parseCarFromLine(const std::string& line) {
    Car car;
    std::stringstream ss(line);
    std::string field;
    std::vector<std::string> fields;
    
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    
    if (fields.size() >= 12) {
        try {
            car.setCarId(std::stoi(fields[0]));
            car.setMake(fields[1]);
            car.setModel(fields[2]);
            car.setYear(std::stoi(fields[3]));
            car.setColor(fields[4]);
            car.setLicensePlate(fields[5]);
            car.setDailyRate(std::stod(fields[6]));
            car.setStatus(Car::stringToStatus(fields[7]));
            car.setMileage(std::stoi(fields[8]));
            car.setFuelType(Car::stringToFuelType(fields[9]));
            car.setTransmission(Car::stringToTransmission(fields[10]));
            car.setSeats(std::stoi(fields[11]));
        } catch (const std::exception& e) {
            // Return empty car if parsing fails
            return Car();
        }
    }
    
    return car;
}

std::string CarService::carToCsvLine(const Car& car) {
    std::stringstream ss;
    ss << car.getCarId() << ","
       << car.getMake() << ","
       << car.getModel() << ","
       << car.getYear() << ","
       << car.getColor() << ","
       << car.getLicensePlate() << ","
       << car.getDailyRate() << ","
       << Car::statusToString(car.getStatus()) << ","
       << car.getMileage() << ","
       << Car::fuelTypeToString(car.getFuelType()) << ","
       << Car::transmissionToString(car.getTransmission()) << ","
       << car.getSeats();
    return ss.str();
}

void CarService::updateNextId(const std::vector<Car>& cars) {
    int maxId = 0;
    for (const auto& car : cars) {
        if (car.getCarId() > maxId) {
            maxId = car.getCarId();
        }
    }
    nextId = maxId + 1;
}
