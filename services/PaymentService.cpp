#include "PaymentService.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const double PaymentService::TAX_RATE = 0.08; // 8% tax rate

bool PaymentService::processPayment(double amount, const std::string& paymentMethod) {
    if (!validatePayment(amount)) {
        return false;
    }
    
    // In a real application, this would integrate with payment gateways
    std::cout << "Processing payment of $" << std::fixed << std::setprecision(2) << amount 
              << " via " << paymentMethod << "..." << std::endl;
    
    // Simulate payment processing
    std::cout << "Payment processed successfully!" << std::endl;
    return true;
}

bool PaymentService::validatePayment(double amount) {
    return amount > 0.0 && amount <= 10000.0; // Basic validation
}

std::string PaymentService::generateReceipt(int bookingId, double amount, const std::string& paymentMethod) {
    std::stringstream receipt;
    double tax = amount * TAX_RATE;
    double total = amount + tax;
    
    receipt << "=== PAYMENT RECEIPT ===" << std::endl;
    receipt << "Booking ID: " << bookingId << std::endl;
    receipt << "Base Amount: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    receipt << "Tax (" << (TAX_RATE * 100) << "%): $" << tax << std::endl;
    receipt << "Total: $" << total << std::endl;
    receipt << "Payment Method: " << paymentMethod << std::endl;
    receipt << "Date: " << "2024-01-01" << std::endl; // In real app, use current date
    receipt << "=========================" << std::endl;
    
    return receipt.str();
}

double PaymentService::calculateTotalWithTax(double baseAmount) {
    return baseAmount + (baseAmount * TAX_RATE);
}
