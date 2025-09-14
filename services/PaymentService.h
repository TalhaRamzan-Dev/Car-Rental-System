#ifndef PAYMENTSERVICE_H
#define PAYMENTSERVICE_H

#include <string>

class PaymentService {
public:
    static bool processPayment(double amount, const std::string& paymentMethod);
    static bool validatePayment(double amount);
    static std::string generateReceipt(int bookingId, double amount, const std::string& paymentMethod);
    static double calculateTotalWithTax(double baseAmount);
    
private:
    static const double TAX_RATE;
};

#endif // PAYMENTSERVICE_H
