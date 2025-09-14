#include "Customer.h"
#include <sstream>
#include <regex>
#include <ctime>

// Constructors
Customer::Customer() : customerId(0) {
}

Customer::Customer(const std::string& firstName, const std::string& lastName, 
                   const std::string& email, const std::string& phone, 
                   const std::string& address, const std::string& licenseNumber, 
                   const std::string& licenseExpiry)
    : customerId(0), firstName(firstName), lastName(lastName), email(email), 
      phone(phone), address(address), licenseNumber(licenseNumber), licenseExpiry(licenseExpiry) {
}

// Getters
int Customer::getCustomerId() const { return customerId; }
const std::string& Customer::getFirstName() const { return firstName; }
const std::string& Customer::getLastName() const { return lastName; }
const std::string& Customer::getEmail() const { return email; }
const std::string& Customer::getPhone() const { return phone; }
const std::string& Customer::getAddress() const { return address; }
const std::string& Customer::getLicenseNumber() const { return licenseNumber; }
const std::string& Customer::getLicenseExpiry() const { return licenseExpiry; }

// Setters
void Customer::setCustomerId(int customerId) { this->customerId = customerId; }
void Customer::setFirstName(const std::string& firstName) { this->firstName = firstName; }
void Customer::setLastName(const std::string& lastName) { this->lastName = lastName; }
void Customer::setEmail(const std::string& email) { this->email = email; }
void Customer::setPhone(const std::string& phone) { this->phone = phone; }
void Customer::setAddress(const std::string& address) { this->address = address; }
void Customer::setLicenseNumber(const std::string& licenseNumber) { this->licenseNumber = licenseNumber; }
void Customer::setLicenseExpiry(const std::string& licenseExpiry) { this->licenseExpiry = licenseExpiry; }

// Utility methods
std::string Customer::getFullName() const {
    return firstName + " " + lastName;
}

bool Customer::isLicenseValid() const {
    if (licenseExpiry.empty()) return false;
    
    // Simple date validation (assuming format YYYY-MM-DD)
    std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
    if (!std::regex_match(licenseExpiry, dateRegex)) return false;
    
    // Check if license is not expired
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    int currentYear = 1900 + timeinfo->tm_year;
    int currentMonth = 1 + timeinfo->tm_mon;
    int currentDay = timeinfo->tm_mday;
    
    int year, month, day;
    sscanf(licenseExpiry.c_str(), "%d-%d-%d", &year, &month, &day);
    
    if (year < currentYear) return false;
    if (year == currentYear && month < currentMonth) return false;
    if (year == currentYear && month == currentMonth && day < currentDay) return false;
    
    return true;
}

// Display methods
void Customer::display() const {
    std::cout << "=== Customer Details ===" << std::endl;
    std::cout << "ID: " << customerId << std::endl;
    std::cout << "Name: " << getFullName() << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Address: " << address << std::endl;
    std::cout << "License Number: " << licenseNumber << std::endl;
    std::cout << "License Expiry: " << licenseExpiry << std::endl;
    std::cout << "License Valid: " << (isLicenseValid() ? "Yes" : "No") << std::endl;
}

void Customer::displaySummary() const {
    std::cout << "[" << customerId << "] " << getFullName() 
              << " - " << email << " - License: " << (isLicenseValid() ? "Valid" : "Invalid") << std::endl;
}

// Validation methods
bool Customer::isValid() const {
    return !firstName.empty() && !lastName.empty() && isValidEmail(email) &&
           isValidPhone(phone) && !address.empty() && isValidLicenseNumber(licenseNumber) &&
           !licenseExpiry.empty();
}

std::string Customer::getValidationErrors() const {
    std::stringstream errors;
    if (firstName.empty()) errors << "First name is required. ";
    if (lastName.empty()) errors << "Last name is required. ";
    if (!isValidEmail(email)) errors << "Valid email is required. ";
    if (!isValidPhone(phone)) errors << "Valid phone number is required. ";
    if (address.empty()) errors << "Address is required. ";
    if (!isValidLicenseNumber(licenseNumber)) errors << "Valid license number is required. ";
    if (licenseExpiry.empty()) errors << "License expiry date is required. ";
    return errors.str();
}

// Static utility methods
bool Customer::isValidEmail(const std::string& email) {
    std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, emailRegex);
}

bool Customer::isValidPhone(const std::string& phone) {
    // Remove all non-digit characters
    std::string digits;
    for (char c : phone) {
        if (std::isdigit(c)) {
            digits += c;
        }
    }
    // Check if it has 10 digits (US phone number)
    return digits.length() == 10;
}

bool Customer::isValidLicenseNumber(const std::string& licenseNumber) {
    // Basic validation - should be alphanumeric and at least 5 characters
    if (licenseNumber.length() < 5) return false;
    for (char c : licenseNumber) {
        if (!std::isalnum(c)) return false;
    }
    return true;
}
