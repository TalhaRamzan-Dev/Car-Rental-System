#include "FileManager.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path.c_str())
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path.c_str(), 0755)
#endif

FileManager::FileManager() : dataDirectory("data") {
}

bool FileManager::initializeDataDirectory() {
    try {
        // Create main data directory
        if (!createDirectory(dataDirectory)) {
            std::cout << "Failed to create data directory: " << dataDirectory << std::endl;
            return false;
        }
        
        // Create backups directory
        std::string backupsDir = dataDirectory + "/backups";
        if (!createDirectory(backupsDir)) {
            std::cout << "Failed to create backups directory: " << backupsDir << std::endl;
            return false;
        }
        
        // Create CSV files if they don't exist
        std::vector<std::string> files = {
            "cars.csv",
            "customers.csv", 
            "bookings.csv"
        };
        
        for (const auto& file : files) {
            std::string filepath = dataDirectory + "/" + file;
            if (!fileExists(filepath)) {
                if (!createDataFile(filepath)) {
                    std::cout << "Failed to create data file: " << filepath << std::endl;
                    return false;
                }
            }
        }
        
        std::cout << "Data directory initialized successfully!" << std::endl;
        return true;
        
    } catch (const std::exception& e) {
        std::cout << "Error initializing data directory: " << e.what() << std::endl;
        return false;
    }
}

bool FileManager::createDataFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    // Write appropriate header based on filename
    if (filename.find("cars.csv") != std::string::npos) {
        file << "ID,Make,Model,Year,Color,LicensePlate,DailyRate,Status,Mileage,FuelType,Transmission,Seats\n";
    } else if (filename.find("customers.csv") != std::string::npos) {
        file << "ID,FirstName,LastName,Email,Phone,Address,LicenseNumber,LicenseExpiry\n";
    } else if (filename.find("bookings.csv") != std::string::npos) {
        file << "ID,CustomerID,CarID,StartDate,EndDate,TotalCost,Status,Notes\n";
    }
    
    file.close();
    return true;
}

bool FileManager::fileExists(const std::string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

std::string FileManager::getDataDirectory() {
    return dataDirectory;
}

bool FileManager::createDirectory(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return true; // Directory already exists
    }
    
    return MKDIR(path) == 0;
}
