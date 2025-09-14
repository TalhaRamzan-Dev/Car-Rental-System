#include "CustomerUI.h"
#include <iostream>
#include <iomanip>

CustomerUI::CustomerUI() {
}

void CustomerUI::showMainMenu() {
    Menu menu("Customer Management");
    
    menu.addOption("Add New Customer", [this]() { addCustomer(); });
    menu.addOption("View All Customers", [this]() { viewAllCustomers(); });
    menu.addOption("View Customer by ID", [this]() { viewCustomerById(); });
    menu.addOption("Search Customers", [this]() { searchCustomers(); });
    menu.addOption("Update Customer", [this]() { updateCustomer(); });
    menu.addOption("Delete Customer", [this]() { deleteCustomer(); });
    
    menu.run();
}

void CustomerUI::addCustomer() {
    Menu::displayHeader("Add New Customer");
    
    Customer customer = createCustomerFromInput();
    if (!customer.isValid()) {
        Menu::displayError("Invalid customer data: " + customer.getValidationErrors());
        Menu::pause();
        return;
    }
    
    if (customerService.addCustomer(customer)) {
        Menu::displaySuccess("Customer added successfully!");
    } else {
        Menu::displayError("Failed to add customer. Please try again.");
    }
    
    Menu::pause();
}

void CustomerUI::viewAllCustomers() {
    Menu::displayHeader("All Customers");
    
    std::vector<Customer> customers = customerService.getAllCustomers();
    if (customers.empty()) {
        Menu::displayInfo("No customers found.");
    } else {
        displayCustomers(customers);
    }
    
    Menu::pause();
}

void CustomerUI::viewCustomerById() {
    Menu::displayHeader("View Customer by ID");
    
    int customerId = Menu::getPositiveInt("Enter Customer ID: ");
    Customer customer = customerService.getCustomerById(customerId);
    
    if (customer.getCustomerId() == 0) {
        Menu::displayError("Customer not found with ID: " + std::to_string(customerId));
    } else {
        displayCustomer(customer);
    }
    
    Menu::pause();
}

void CustomerUI::searchCustomers() {
    Menu::displayHeader("Search Customers");
    
    std::string searchTerm = Menu::getNonEmptyString("Enter search term: ");
    std::vector<Customer> results = customerService.searchCustomers(searchTerm);
    
    if (results.empty()) {
        Menu::displayInfo("No customers found matching: " + searchTerm);
    } else {
        std::cout << "Found " << results.size() << " customer(s) matching: " << searchTerm << std::endl;
        displayCustomers(results);
    }
    
    Menu::pause();
}

void CustomerUI::updateCustomer() {
    Menu::displayHeader("Update Customer");
    
    int customerId = Menu::getPositiveInt("Enter Customer ID to update: ");
    Customer customer = customerService.getCustomerById(customerId);
    
    if (customer.getCustomerId() == 0) {
        Menu::displayError("Customer not found with ID: " + std::to_string(customerId));
        Menu::pause();
        return;
    }
    
    displayCustomer(customer);
    std::cout << "\nEnter new details:" << std::endl;
    updateCustomerFromInput(customer);
    
    if (!customer.isValid()) {
        Menu::displayError("Invalid customer data: " + customer.getValidationErrors());
        Menu::pause();
        return;
    }
    
    if (customerService.updateCustomer(customer)) {
        Menu::displaySuccess("Customer updated successfully!");
    } else {
        Menu::displayError("Failed to update customer. Please try again.");
    }
    
    Menu::pause();
}

void CustomerUI::deleteCustomer() {
    Menu::displayHeader("Delete Customer");
    
    int customerId = Menu::getPositiveInt("Enter Customer ID to delete: ");
    Customer customer = customerService.getCustomerById(customerId);
    
    if (customer.getCustomerId() == 0) {
        Menu::displayError("Customer not found with ID: " + std::to_string(customerId));
        Menu::pause();
        return;
    }
    
    displayCustomer(customer);
    
    if (Menu::getYesNo("Are you sure you want to delete this customer?")) {
        if (customerService.deleteCustomer(customerId)) {
            Menu::displaySuccess("Customer deleted successfully!");
        } else {
            Menu::displayError("Failed to delete customer. Please try again.");
        }
    } else {
        Menu::displayInfo("Deletion cancelled.");
    }
    
    Menu::pause();
}

void CustomerUI::displayCustomer(const Customer& customer) {
    customer.display();
}

void CustomerUI::displayCustomers(const std::vector<Customer>& customers) {
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(25) << "Email" 
              << std::setw(15) << "Phone" 
              << std::setw(10) << "License" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& customer : customers) {
        std::cout << std::left << std::setw(5) << customer.getCustomerId()
                  << std::setw(20) << customer.getFullName()
                  << std::setw(25) << customer.getEmail()
                  << std::setw(15) << customer.getPhone()
                  << std::setw(10) << (customer.isLicenseValid() ? "Valid" : "Invalid")
                  << std::endl;
    }
}

Customer CustomerUI::createCustomerFromInput() {
    Customer customer;
    
    customer.setFirstName(Menu::getNonEmptyString("Enter First Name: "));
    customer.setLastName(Menu::getNonEmptyString("Enter Last Name: "));
    customer.setEmail(Menu::getNonEmptyString("Enter Email: "));
    customer.setPhone(Menu::getNonEmptyString("Enter Phone: "));
    customer.setAddress(Menu::getNonEmptyString("Enter Address: "));
    customer.setLicenseNumber(Menu::getNonEmptyString("Enter License Number: "));
    customer.setLicenseExpiry(Menu::getNonEmptyString("Enter License Expiry (YYYY-MM-DD): "));
    
    return customer;
}

void CustomerUI::updateCustomerFromInput(Customer& customer) {
    std::string input;
    
    std::cout << "First Name [" << customer.getFirstName() << "]: ";
    input = Menu::getString("First Name [" + customer.getFirstName() + "]: ");
    if (!input.empty()) customer.setFirstName(input);
    
    std::cout << "Last Name [" << customer.getLastName() << "]: ";
    input = Menu::getString("Last Name [" + customer.getLastName() + "]: ");
    if (!input.empty()) customer.setLastName(input);
    
    std::cout << "Email [" << customer.getEmail() << "]: ";
    input = Menu::getString("Email [" + customer.getEmail() + "]: ");
    if (!input.empty()) customer.setEmail(input);
    
    std::cout << "Phone [" << customer.getPhone() << "]: ";
    input = Menu::getString("Phone [" + customer.getPhone() + "]: ");
    if (!input.empty()) customer.setPhone(input);
    
    std::cout << "Address [" << customer.getAddress() << "]: ";
    input = Menu::getString("Address [" + customer.getAddress() + "]: ");
    if (!input.empty()) customer.setAddress(input);
    
    std::cout << "License Number [" << customer.getLicenseNumber() << "]: ";
    input = Menu::getString("License Number [" + customer.getLicenseNumber() + "]: ");
    if (!input.empty()) customer.setLicenseNumber(input);
    
    std::cout << "License Expiry [" << customer.getLicenseExpiry() << "]: ";
    input = Menu::getString("License Expiry [" + customer.getLicenseExpiry() + "]: ");
    if (!input.empty()) customer.setLicenseExpiry(input);
}
