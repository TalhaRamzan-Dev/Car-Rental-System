#include "Booking.h"
#include <sstream>
#include <regex>
#include <ctime>

// Constructors
Booking::Booking() : bookingId(0), customerId(0), carId(0), totalCost(0.0), status("Active") {
}

Booking::Booking(int customerId, int carId, const std::string& startDate, 
                 const std::string& endDate, double totalCost, const std::string& status)
    : bookingId(0), customerId(customerId), carId(carId), startDate(startDate), 
      endDate(endDate), totalCost(totalCost), status(status) {
}

// Getters
int Booking::getBookingId() const { return bookingId; }
int Booking::getCustomerId() const { return customerId; }
int Booking::getCarId() const { return carId; }
const std::string& Booking::getStartDate() const { return startDate; }
const std::string& Booking::getEndDate() const { return endDate; }
double Booking::getTotalCost() const { return totalCost; }
const std::string& Booking::getStatus() const { return status; }
const std::string& Booking::getNotes() const { return notes; }

// Setters
void Booking::setBookingId(int bookingId) { this->bookingId = bookingId; }
void Booking::setCustomerId(int customerId) { this->customerId = customerId; }
void Booking::setCarId(int carId) { this->carId = carId; }
void Booking::setStartDate(const std::string& startDate) { this->startDate = startDate; }
void Booking::setEndDate(const std::string& endDate) { this->endDate = endDate; }
void Booking::setTotalCost(double totalCost) { this->totalCost = totalCost; }
void Booking::setStatus(const std::string& status) { this->status = status; }
void Booking::setNotes(const std::string& notes) { this->notes = notes; }

// Utility methods
int Booking::getDuration() const {
    return daysBetween(startDate, endDate);
}

bool Booking::isActive() const {
    return status == "Active";
}

bool Booking::isCompleted() const {
    return status == "Completed";
}

bool Booking::isCancelled() const {
    return status == "Cancelled";
}

double Booking::calculateCost(double dailyRate) const {
    return getDuration() * dailyRate;
}

// Display methods
void Booking::display() const {
    std::cout << "=== Booking Details ===" << std::endl;
    std::cout << "ID: " << bookingId << std::endl;
    std::cout << "Customer ID: " << customerId << std::endl;
    std::cout << "Car ID: " << carId << std::endl;
    std::cout << "Start Date: " << startDate << std::endl;
    std::cout << "End Date: " << endDate << std::endl;
    std::cout << "Duration: " << getDuration() << " days" << std::endl;
    std::cout << "Total Cost: $" << totalCost << std::endl;
    std::cout << "Status: " << status << std::endl;
    if (!notes.empty()) {
        std::cout << "Notes: " << notes << std::endl;
    }
}

void Booking::displaySummary() const {
    std::cout << "[" << bookingId << "] Customer " << customerId << " - Car " << carId 
              << " (" << startDate << " to " << endDate << ") - $" << totalCost 
              << " - " << status << std::endl;
}

// Validation methods
bool Booking::isValid() const {
    return customerId > 0 && carId > 0 && isValidDate(startDate) && 
           isValidDate(endDate) && isDateAfter(endDate, startDate) && totalCost >= 0;
}

std::string Booking::getValidationErrors() const {
    std::stringstream errors;
    if (customerId <= 0) errors << "Valid customer ID is required. ";
    if (carId <= 0) errors << "Valid car ID is required. ";
    if (!isValidDate(startDate)) errors << "Valid start date is required. ";
    if (!isValidDate(endDate)) errors << "Valid end date is required. ";
    if (!isDateAfter(endDate, startDate)) errors << "End date must be after start date. ";
    if (totalCost < 0) errors << "Total cost cannot be negative. ";
    return errors.str();
}

// Static utility methods
bool Booking::isValidDate(const std::string& date) {
    std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
    if (!std::regex_match(date, dateRegex)) return false;
    
    int year, month, day;
    if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3) return false;
    
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    
    // Basic month day validation
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
    if (month == 2 && day > 29) return false;
    
    return true;
}

bool Booking::isDateAfter(const std::string& date1, const std::string& date2) {
    int year1, month1, day1, year2, month2, day2;
    sscanf(date1.c_str(), "%d-%d-%d", &year1, &month1, &day1);
    sscanf(date2.c_str(), "%d-%d-%d", &year2, &month2, &day2);
    
    if (year1 > year2) return true;
    if (year1 < year2) return false;
    if (month1 > month2) return true;
    if (month1 < month2) return false;
    return day1 > day2;
}

int Booking::daysBetween(const std::string& startDate, const std::string& endDate) {
    int year1, month1, day1, year2, month2, day2;
    sscanf(startDate.c_str(), "%d-%d-%d", &year1, &month1, &day1);
    sscanf(endDate.c_str(), "%d-%d-%d", &year2, &month2, &day2);
    
    // Simple calculation - in a real application, you'd use a proper date library
    int days1 = year1 * 365 + month1 * 30 + day1;
    int days2 = year2 * 365 + month2 * 30 + day2;
    
    return days2 - days1;
}
