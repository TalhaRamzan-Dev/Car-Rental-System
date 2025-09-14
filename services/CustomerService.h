#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include "../models/Customer.h"
#include <vector>
#include <string>

class CustomerService {
private:
    std::string dataFile;
    int nextId;

public:
    CustomerService();
    
    // CRUD operations
    bool addCustomer(const Customer& customer);
    std::vector<Customer> getAllCustomers();
    Customer getCustomerById(int customerId);
    std::vector<Customer> searchCustomers(const std::string& searchTerm);
    bool updateCustomer(const Customer& customer);
    bool deleteCustomer(int customerId);
    
    // Utility methods
    bool saveCustomers(const std::vector<Customer>& customers);
    std::vector<Customer> loadCustomers();
    int getNextId();
    
private:
    Customer parseCustomerFromLine(const std::string& line);
    std::string customerToCsvLine(const Customer& customer);
    void updateNextId(const std::vector<Customer>& customers);
};

#endif // CUSTOMERSERVICE_H
