#include "Car.h"
#include <sstream>
#include <algorithm>

// Constructors
Car::Car() : carId(0), year(0), dailyRate(0.0), status(CarStatus::AVAILABLE), 
             mileage(0), fuelType(FuelType::GASOLINE), transmission(Transmission::MANUAL), seats(0) {
}

Car::Car(const std::string& make, const std::string& model, int year, 
         const std::string& color, const std::string& licensePlate, 
         double dailyRate, FuelType fuelType, Transmission transmission, int seats)
    : carId(0), make(make), model(model), year(year), color(color), 
      licensePlate(licensePlate), dailyRate(dailyRate), status(CarStatus::AVAILABLE),
      mileage(0), fuelType(fuelType), transmission(transmission), seats(seats) {
}

// Getters
int Car::getCarId() const { return carId; }
const std::string& Car::getMake() const { return make; }
const std::string& Car::getModel() const { return model; }
int Car::getYear() const { return year; }
const std::string& Car::getColor() const { return color; }
const std::string& Car::getLicensePlate() const { return licensePlate; }
double Car::getDailyRate() const { return dailyRate; }
CarStatus Car::getStatus() const { return status; }
int Car::getMileage() const { return mileage; }
FuelType Car::getFuelType() const { return fuelType; }
Transmission Car::getTransmission() const { return transmission; }
int Car::getSeats() const { return seats; }

// Setters
void Car::setCarId(int carId) { this->carId = carId; }
void Car::setMake(const std::string& make) { this->make = make; }
void Car::setModel(const std::string& model) { this->model = model; }
void Car::setYear(int year) { this->year = year; }
void Car::setColor(const std::string& color) { this->color = color; }
void Car::setLicensePlate(const std::string& licensePlate) { this->licensePlate = licensePlate; }
void Car::setDailyRate(double dailyRate) { this->dailyRate = dailyRate; }
void Car::setStatus(CarStatus status) { this->status = status; }
void Car::setMileage(int mileage) { this->mileage = mileage; }
void Car::setFuelType(FuelType fuelType) { this->fuelType = fuelType; }
void Car::setTransmission(Transmission transmission) { this->transmission = transmission; }
void Car::setSeats(int seats) { this->seats = seats; }

// Utility methods
std::string Car::getStatusString() const {
    switch (status) {
        case CarStatus::AVAILABLE: return "Available";
        case CarStatus::RENTED: return "Rented";
        case CarStatus::MAINTENANCE: return "Maintenance";
        case CarStatus::RETIRED: return "Retired";
        default: return "Unknown";
    }
}

std::string Car::getFuelTypeString() const {
    switch (fuelType) {
        case FuelType::GASOLINE: return "Gasoline";
        case FuelType::DIESEL: return "Diesel";
        case FuelType::ELECTRIC: return "Electric";
        case FuelType::HYBRID: return "Hybrid";
        default: return "Unknown";
    }
}

std::string Car::getTransmissionString() const {
    switch (transmission) {
        case Transmission::MANUAL: return "Manual";
        case Transmission::AUTOMATIC: return "Automatic";
        default: return "Unknown";
    }
}

void Car::updateMileage(int newMileage) {
    if (newMileage >= mileage) {
        mileage = newMileage;
    }
}

bool Car::isAvailable() const {
    return status == CarStatus::AVAILABLE;
}

double Car::calculateRentalCost(int days) const {
    return dailyRate * days;
}

// Display methods
void Car::display() const {
    std::cout << "=== Car Details ===" << std::endl;
    std::cout << "ID: " << carId << std::endl;
    std::cout << "Make: " << make << std::endl;
    std::cout << "Model: " << model << std::endl;
    std::cout << "Year: " << year << std::endl;
    std::cout << "Color: " << color << std::endl;
    std::cout << "License Plate: " << licensePlate << std::endl;
    std::cout << "Daily Rate: $" << dailyRate << std::endl;
    std::cout << "Status: " << getStatusString() << std::endl;
    std::cout << "Mileage: " << mileage << " miles" << std::endl;
    std::cout << "Fuel Type: " << getFuelTypeString() << std::endl;
    std::cout << "Transmission: " << getTransmissionString() << std::endl;
    std::cout << "Seats: " << seats << std::endl;
}

void Car::displaySummary() const {
    std::cout << "[" << carId << "] " << year << " " << make << " " << model 
              << " - " << getStatusString() << " - $" << dailyRate << "/day" << std::endl;
}

// Validation methods
bool Car::isValid() const {
    return !make.empty() && !model.empty() && year > 1900 && year <= 2025 &&
           !color.empty() && !licensePlate.empty() && dailyRate > 0 && seats > 0;
}

std::string Car::getValidationErrors() const {
    std::stringstream errors;
    if (make.empty()) errors << "Make is required. ";
    if (model.empty()) errors << "Model is required. ";
    if (year <= 1900 || year > 2025) errors << "Year must be between 1901 and 2025. ";
    if (color.empty()) errors << "Color is required. ";
    if (licensePlate.empty()) errors << "License plate is required. ";
    if (dailyRate <= 0) errors << "Daily rate must be positive. ";
    if (seats <= 0) errors << "Seats must be positive. ";
    return errors.str();
}

// Static utility methods
CarStatus Car::stringToStatus(const std::string& statusStr) {
    std::string lower = statusStr;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    if (lower == "available") return CarStatus::AVAILABLE;
    if (lower == "rented") return CarStatus::RENTED;
    if (lower == "maintenance") return CarStatus::MAINTENANCE;
    if (lower == "retired") return CarStatus::RETIRED;
    return CarStatus::AVAILABLE;
}

std::string Car::statusToString(CarStatus status) {
    switch (status) {
        case CarStatus::AVAILABLE: return "Available";
        case CarStatus::RENTED: return "Rented";
        case CarStatus::MAINTENANCE: return "Maintenance";
        case CarStatus::RETIRED: return "Retired";
        default: return "Available";
    }
}

FuelType Car::stringToFuelType(const std::string& fuelStr) {
    std::string lower = fuelStr;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    if (lower == "gasoline") return FuelType::GASOLINE;
    if (lower == "diesel") return FuelType::DIESEL;
    if (lower == "electric") return FuelType::ELECTRIC;
    if (lower == "hybrid") return FuelType::HYBRID;
    return FuelType::GASOLINE;
}

std::string Car::fuelTypeToString(FuelType fuelType) {
    switch (fuelType) {
        case FuelType::GASOLINE: return "Gasoline";
        case FuelType::DIESEL: return "Diesel";
        case FuelType::ELECTRIC: return "Electric";
        case FuelType::HYBRID: return "Hybrid";
        default: return "Gasoline";
    }
}

Transmission Car::stringToTransmission(const std::string& transStr) {
    std::string lower = transStr;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    
    if (lower == "manual") return Transmission::MANUAL;
    if (lower == "automatic") return Transmission::AUTOMATIC;
    return Transmission::MANUAL;
}

std::string Car::transmissionToString(Transmission transmission) {
    switch (transmission) {
        case Transmission::MANUAL: return "Manual";
        case Transmission::AUTOMATIC: return "Automatic";
        default: return "Manual";
    }
}
