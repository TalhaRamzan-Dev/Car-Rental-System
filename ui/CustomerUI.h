#ifndef CUSTOMER_UI_H
#define CUSTOMER_UI_H

#include "../models/Customer.h"
#include "../services/CustomerService.h"
#include "Menu.h"
#include <vector>

class CustomerUI {
private:
    CustomerService customerService;

public:
    CustomerUI();
    
    void showMainMenu();
    void addCustomer();
    void viewAllCustomers();
    void viewCustomerById();
    void searchCustomers();
    void updateCustomer();
    void deleteCustomer();
    
private:
    void displayCustomer(const Customer& customer);
    void displayCustomers(const std::vector<Customer>& customers);
    Customer createCustomerFromInput();
    void updateCustomerFromInput(Customer& customer);
};

#endif // CUSTOMER_UI_H
