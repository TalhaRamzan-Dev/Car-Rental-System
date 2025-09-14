#include "CustomerService.h"
#include <fstream>
#include <sstream>
#include <algorithm>

CustomerService::CustomerService() : dataFile("data/customers.csv"), nextId(1) {
    loadCustomers();
}

bool CustomerService::addCustomer(const Customer& customer) {
    std::vector<Customer> customers = loadCustomers();
    Customer newCustomer = customer;
    newCustomer.setCustomerId(getNextId());
    customers.push_back(newCustomer);
    nextId++;
    return saveCustomers(customers);
}

std::vector<Customer> CustomerService::getAllCustomers() {
    return loadCustomers();
}

Customer CustomerService::getCustomerById(int customerId) {
    std::vector<Customer> customers = loadCustomers();
    for (const auto& customer : customers) {
        if (customer.getCustomerId() == customerId) {
            return customer;
        }
    }
    return Customer();
}

std::vector<Customer> CustomerService::searchCustomers(const std::string& searchTerm) {
    std::vector<Customer> customers = loadCustomers();
    std::vector<Customer> results;
    std::string lowerSearchTerm = searchTerm;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);
    
    for (const auto& customer : customers) {
        std::string name = customer.getFullName();
        std::string email = customer.getEmail();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        std::transform(email.begin(), email.end(), email.begin(), ::tolower);
        
        if (name.find(lowerSearchTerm) != std::string::npos ||
            email.find(lowerSearchTerm) != std::string::npos) {
            results.push_back(customer);
        }
    }
    return results;
}

bool CustomerService::updateCustomer(const Customer& customer) {
    std::vector<Customer> customers = loadCustomers();
    for (auto& c : customers) {
        if (c.getCustomerId() == customer.getCustomerId()) {
            c = customer;
            return saveCustomers(customers);
        }
    }
    return false;
}

bool CustomerService::deleteCustomer(int customerId) {
    std::vector<Customer> customers = loadCustomers();
    auto it = std::remove_if(customers.begin(), customers.end(),
        [customerId](const Customer& customer) { return customer.getCustomerId() == customerId; });
    
    if (it != customers.end()) {
        customers.erase(it, customers.end());
        return saveCustomers(customers);
    }
    return false;
}

bool CustomerService::saveCustomers(const std::vector<Customer>& customers) {
    std::ofstream file(dataFile);
    if (!file.is_open()) return false;
    
    file << "ID,FirstName,LastName,Email,Phone,Address,LicenseNumber,LicenseExpiry\n";
    for (const auto& customer : customers) {
        file << customerToCsvLine(customer) << "\n";
    }
    file.close();
    return true;
}

std::vector<Customer> CustomerService::loadCustomers() {
    std::vector<Customer> customers;
    std::ifstream file(dataFile);
    if (!file.is_open()) return customers;
    
    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine) { firstLine = false; continue; }
        if (!line.empty()) {
            Customer customer = parseCustomerFromLine(line);
            if (customer.getCustomerId() > 0) {
                customers.push_back(customer);
            }
        }
    }
    file.close();
    updateNextId(customers);
    return customers;
}

int CustomerService::getNextId() { return nextId; }

Customer CustomerService::parseCustomerFromLine(const std::string& line) {
    Customer customer;
    std::stringstream ss(line);
    std::string field;
    std::vector<std::string> fields;
    
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    
    if (fields.size() >= 8) {
        try {
            customer.setCustomerId(std::stoi(fields[0]));
            customer.setFirstName(fields[1]);
            customer.setLastName(fields[2]);
            customer.setEmail(fields[3]);
            customer.setPhone(fields[4]);
            customer.setAddress(fields[5]);
            customer.setLicenseNumber(fields[6]);
            customer.setLicenseExpiry(fields[7]);
        } catch (const std::exception& e) {
            return Customer();
        }
    }
    return customer;
}

std::string CustomerService::customerToCsvLine(const Customer& customer) {
    std::stringstream ss;
    ss << customer.getCustomerId() << ","
       << customer.getFirstName() << ","
       << customer.getLastName() << ","
       << customer.getEmail() << ","
       << customer.getPhone() << ","
       << customer.getAddress() << ","
       << customer.getLicenseNumber() << ","
       << customer.getLicenseExpiry();
    return ss.str();
}

void CustomerService::updateNextId(const std::vector<Customer>& customers) {
    int maxId = 0;
    for (const auto& customer : customers) {
        if (customer.getCustomerId() > maxId) {
            maxId = customer.getCustomerId();
        }
    }
    nextId = maxId + 1;
}
