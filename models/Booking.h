#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <iostream>

class Booking {
private:
    int bookingId;
    int customerId;
    int carId;
    std::string startDate;
    std::string endDate;
    double totalCost;
    std::string status;
    std::string notes;

public:
    // Constructors
    Booking();
    Booking(int customerId, int carId, const std::string& startDate, 
            const std::string& endDate, double totalCost, const std::string& status = "Active");
    
    // Getters
    int getBookingId() const;
    int getCustomerId() const;
    int getCarId() const;
    const std::string& getStartDate() const;
    const std::string& getEndDate() const;
    double getTotalCost() const;
    const std::string& getStatus() const;
    const std::string& getNotes() const;
    
    // Setters
    void setBookingId(int bookingId);
    void setCustomerId(int customerId);
    void setCarId(int carId);
    void setStartDate(const std::string& startDate);
    void setEndDate(const std::string& endDate);
    void setTotalCost(double totalCost);
    void setStatus(const std::string& status);
    void setNotes(const std::string& notes);
    
    // Utility methods
    int getDuration() const;
    bool isActive() const;
    bool isCompleted() const;
    bool isCancelled() const;
    double calculateCost(double dailyRate) const;
    
    // Display methods
    void display() const;
    void displaySummary() const;
    
    // Validation methods
    bool isValid() const;
    std::string getValidationErrors() const;
    
    // Static utility methods
    static bool isValidDate(const std::string& date);
    static bool isDateAfter(const std::string& date1, const std::string& date2);
    static int daysBetween(const std::string& startDate, const std::string& endDate);
};

#endif // BOOKING_H
