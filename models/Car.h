#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>

enum class CarStatus {
    AVAILABLE,
    RENTED,
    MAINTENANCE,
    RETIRED
};

enum class FuelType {
    GASOLINE,
    DIESEL,
    ELECTRIC,
    HYBRID
};

enum class Transmission {
    MANUAL,
    AUTOMATIC
};

class Car {
private:
    int carId;
    std::string make;
    std::string model;
    int year;
    std::string color;
    std::string licensePlate;
    double dailyRate;
    CarStatus status;
    int mileage;
    FuelType fuelType;
    Transmission transmission;
    int seats;

public:
    // Constructors
    Car();
    Car(const std::string& make, const std::string& model, int year, 
        const std::string& color, const std::string& licensePlate, 
        double dailyRate, FuelType fuelType, Transmission transmission, int seats);
    
    // Getters
    int getCarId() const;
    const std::string& getMake() const;
    const std::string& getModel() const;
    int getYear() const;
    const std::string& getColor() const;
    const std::string& getLicensePlate() const;
    double getDailyRate() const;
    CarStatus getStatus() const;
    int getMileage() const;
    FuelType getFuelType() const;
    Transmission getTransmission() const;
    int getSeats() const;
    
    // Setters
    void setCarId(int carId);
    void setMake(const std::string& make);
    void setModel(const std::string& model);
    void setYear(int year);
    void setColor(const std::string& color);
    void setLicensePlate(const std::string& licensePlate);
    void setDailyRate(double dailyRate);
    void setStatus(CarStatus status);
    void setMileage(int mileage);
    void setFuelType(FuelType fuelType);
    void setTransmission(Transmission transmission);
    void setSeats(int seats);
    
    // Utility methods
    std::string getStatusString() const;
    std::string getFuelTypeString() const;
    std::string getTransmissionString() const;
    void updateMileage(int newMileage);
    bool isAvailable() const;
    double calculateRentalCost(int days) const;
    
    // Display methods
    void display() const;
    void displaySummary() const;
    
    // Validation methods
    bool isValid() const;
    std::string getValidationErrors() const;
    
    // Static utility methods
    static CarStatus stringToStatus(const std::string& statusStr);
    static std::string statusToString(CarStatus status);
    static FuelType stringToFuelType(const std::string& fuelStr);
    static std::string fuelTypeToString(FuelType fuelType);
    static Transmission stringToTransmission(const std::string& transStr);
    static std::string transmissionToString(Transmission transmission);
};

#endif // CAR_H
