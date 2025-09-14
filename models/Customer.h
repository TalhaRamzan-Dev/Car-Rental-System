#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
private:
    int customerId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    std::string address;
    std::string licenseNumber;
    std::string licenseExpiry;

public:
    // Constructors
    Customer();
    Customer(const std::string& firstName, const std::string& lastName, 
             const std::string& email, const std::string& phone, 
             const std::string& address, const std::string& licenseNumber, 
             const std::string& licenseExpiry);
    
    // Getters
    int getCustomerId() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    const std::string& getEmail() const;
    const std::string& getPhone() const;
    const std::string& getAddress() const;
    const std::string& getLicenseNumber() const;
    const std::string& getLicenseExpiry() const;
    
    // Setters
    void setCustomerId(int customerId);
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setAddress(const std::string& address);
    void setLicenseNumber(const std::string& licenseNumber);
    void setLicenseExpiry(const std::string& licenseExpiry);
    
    // Utility methods
    std::string getFullName() const;
    bool isLicenseValid() const;
    
    // Display methods
    void display() const;
    void displaySummary() const;
    
    // Validation methods
    bool isValid() const;
    std::string getValidationErrors() const;
    
    // Static utility methods
    static bool isValidEmail(const std::string& email);
    static bool isValidPhone(const std::string& phone);
    static bool isValidLicenseNumber(const std::string& licenseNumber);
};

#endif // CUSTOMER_H
