# Car Rental Management System

A comprehensive C++ application for managing car rentals with a file-based data storage system using CSV files.

## 🚀 Features

### Core Functionality
- **Complete CRUD Operations** for Cars, Customers, and Bookings
- **File-based Data Storage** using CSV format (no database required)
- **Menu-driven Interface** with intuitive navigation
- **Search and Filter Capabilities** across all entities
- **Data Validation** with comprehensive error handling
- **Statistics and Reporting** for business insights

### Car Management
- Add, view, update, and delete cars
- Track car details (make, model, year, color, license plate, etc.)
- Monitor car status (Available, Rented, Maintenance, Retired)
- Search cars by various criteria
- View available cars for rental
- Generate car statistics

### Customer Management
- Complete customer profile management
- License validation and expiry tracking
- Email and phone number validation
- Search customers by name or email
- Customer booking history

### Booking Management
- Create new bookings with customer and car selection
- Track booking status (Active, Completed, Cancelled)
- Automatic cost calculation based on daily rates
- Date validation and duration calculation
- View bookings by customer or car
- Filter active bookings

## 🛠️ Technical Details

### Architecture
- **Object-Oriented Design** with clear separation of concerns
- **Model-View-Controller (MVC)** pattern implementation
- **Service Layer** for business logic
- **File-based Persistence** using CSV format

### Dependencies
- **C++17** or later
- **Standard Library Only** - no external dependencies
- **Cross-platform** compatible (Windows, Linux, macOS)

### File Structure
```
Car Rental System/
├── CarRentalSystem.exe          # Compiled executable
├── main.cpp                     # Application entry point
├── models/                      # Data models
│   ├── Car.h/cpp               # Car entity
│   ├── Customer.h/cpp          # Customer entity
│   └── Booking.h/cpp           # Booking entity
├── services/                    # Business logic
│   ├── CarService.h/cpp        # Car operations
│   ├── CustomerService.h/cpp   # Customer operations
│   ├── BookingService.h/cpp    # Booking operations
│   └── PaymentService.h/cpp    # Payment utilities
├── ui/                         # User interface
│   ├── Menu.h/cpp              # Base menu system
│   ├── CarUI.h/cpp             # Car management UI
│   ├── CustomerUI.h/cpp        # Customer management UI
│   └── BookingUI.h/cpp         # Booking management UI
├── database/                    # Data persistence
│   └── FileManager.h/cpp       # File operations
└── data/                       # Data storage
    ├── cars.csv                # Car data
    ├── customers.csv           # Customer data
    ├── bookings.csv            # Booking data
    └── backups/                # Backup files
```

## 🚀 Getting Started

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- C++17 support

### Compilation
```bash
# Using g++
g++ -std=c++17 -o CarRentalSystem main.cpp models/*.cpp services/*.cpp ui/*.cpp database/*.cpp

# Using Visual Studio
# Open the project in Visual Studio and build
```

### Running the Application
```bash
# Windows
./CarRentalSystem.exe

# Linux/macOS
./CarRentalSystem
```

## 📖 Usage Guide

### Main Menu
1. **Car Management** - Manage the car fleet
2. **Customer Management** - Handle customer records
3. **Booking Management** - Process rental bookings
4. **System Information** - View system details
5. **Exit** - Close the application

### Car Management
- **Add New Car**: Enter car details including make, model, year, color, license plate, daily rate, fuel type, transmission, and seating capacity
- **View All Cars**: Display all cars in a formatted table
- **View Car by ID**: Find and display a specific car
- **Search Cars**: Search by make, model, color, or license plate
- **Update Car**: Modify existing car information
- **Delete Car**: Remove a car from the system
- **View Available Cars**: Show only cars available for rental
- **View Statistics**: Display fleet statistics and metrics

### Customer Management
- **Add New Customer**: Create customer profiles with personal and license information
- **View All Customers**: Display all customers in a formatted table
- **View Customer by ID**: Find and display a specific customer
- **Search Customers**: Search by name or email address
- **Update Customer**: Modify existing customer information
- **Delete Customer**: Remove a customer from the system

### Booking Management
- **Add New Booking**: Create rental bookings with customer and car selection
- **View All Bookings**: Display all bookings in a formatted table
- **View Booking by ID**: Find and display a specific booking
- **View Bookings by Customer**: Show all bookings for a specific customer
- **View Bookings by Car**: Show all bookings for a specific car
- **Update Booking**: Modify existing booking information
- **Delete Booking**: Remove a booking from the system
- **View Active Bookings**: Display only currently active bookings

## 💾 Data Storage

### CSV Format
The application uses CSV files for data persistence:

**cars.csv**
```csv
ID,Make,Model,Year,Color,LicensePlate,DailyRate,Status,Mileage,FuelType,Transmission,Seats
1,Toyota,Camry,2020,Silver,ABC123,50.00,Available,15000,Gasoline,Automatic,5
```

**customers.csv**
```csv
ID,FirstName,LastName,Email,Phone,Address,LicenseNumber,LicenseExpiry
1,John,Doe,john.doe@email.com,1234567890,123 Main St,DL123456,2025-12-31
```

**bookings.csv**
```csv
ID,CustomerID,CarID,StartDate,EndDate,TotalCost,Status,Notes
1,1,1,2024-01-01,2024-01-05,250.00,Active,Weekend rental
```

### Data Validation
- **Email Format**: Valid email address format required
- **Phone Numbers**: 10-digit phone number validation
- **License Numbers**: Alphanumeric validation
- **Date Format**: YYYY-MM-DD format required
- **Positive Values**: Daily rates, mileage, and costs must be positive
- **Required Fields**: All essential fields must be provided

## 🔧 Configuration

### Data Directory
The application automatically creates a `data/` directory for storing CSV files and backups.

### Backup System
- Automatic backup creation before major operations
- Backup files stored in `data/backups/` directory
- Manual backup option available

## 🐛 Troubleshooting

### Common Issues

1. **File Permission Errors**
   - Ensure the application has write permissions to the data directory
   - Check if CSV files are not open in another program

2. **Data Corruption**
   - Use backup files from `data/backups/` directory
   - Verify CSV file format matches expected structure

3. **Compilation Errors**
   - Ensure C++17 support is enabled
   - Check all source files are present
   - Verify include paths are correct

### Error Messages
- **"Failed to initialize file system"**: Check directory permissions
- **"Invalid data"**: Verify input format and required fields
- **"File not found"**: Ensure CSV files exist in data directory

## 📊 System Requirements

### Minimum Requirements
- **OS**: Windows 7+, macOS 10.12+, or Linux
- **RAM**: 512 MB
- **Storage**: 10 MB for application and data
- **Compiler**: C++17 compatible

### Recommended
- **OS**: Windows 10+, macOS 10.15+, or Ubuntu 18.04+
- **RAM**: 1 GB
- **Storage**: 100 MB for application and data

## 🤝 Contributing

### Code Style
- Follow C++ naming conventions
- Use meaningful variable and function names
- Add comments for complex logic
- Maintain consistent indentation

### Adding Features
1. Create appropriate model classes for new entities
2. Implement service layer for business logic
3. Add UI components for user interaction
4. Update FileManager for data persistence
5. Add validation and error handling

## 📝 License

This project is open source and available under the MIT License.

## 📞 Support

For questions, issues, or feature requests, please contact the development team.

---

**Version**: 1.0.0  
**Last Updated**: 2024  
**Author**: Car Rental System Development Team
