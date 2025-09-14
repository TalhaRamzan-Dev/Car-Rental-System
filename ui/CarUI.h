#ifndef CAR_UI_H
#define CAR_UI_H

#include "../models/Car.h"
#include "../services/CarService.h"
#include "Menu.h"
#include <vector>

class CarUI {
private:
    CarService carService;

public:
    CarUI();
    
    void showMainMenu();
    void addCar();
    void viewAllCars();
    void viewCarById();
    void searchCars();
    void updateCar();
    void deleteCar();
    void viewAvailableCars();
    void viewStatistics();
    
private:
    void displayCar(const Car& car);
    void displayCars(const std::vector<Car>& cars);
    Car createCarFromInput();
    void updateCarFromInput(Car& car);
};

#endif // CAR_UI_H
