#ifndef CARSERVICE_H
#define CARSERVICE_H

#include "../models/Car.h"
#include <vector>
#include <string>

class CarService {
private:
    std::string dataFile;
    int nextId;

public:
    CarService();
    
    // CRUD operations
    bool addCar(const Car& car);
    std::vector<Car> getAllCars();
    Car getCarById(int carId);
    std::vector<Car> searchCars(const std::string& searchTerm);
    std::vector<Car> getAvailableCars();
    bool updateCar(const Car& car);
    bool deleteCar(int carId);
    
    // Utility methods
    bool saveCars(const std::vector<Car>& cars);
    std::vector<Car> loadCars();
    int getNextId();
    void setNextId(int id);
    
    // Statistics
    int getTotalCars();
    int getAvailableCarsCount();
    int getRentedCarsCount();
    int getMaintenanceCarsCount();
    double getAverageDailyRate();
    
private:
    Car parseCarFromLine(const std::string& line);
    std::string carToCsvLine(const Car& car);
    void updateNextId(const std::vector<Car>& cars);
};

#endif // CARSERVICE_H
