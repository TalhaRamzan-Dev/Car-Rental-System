# 🚗 Car Rental Management System

A **C++17 application** for managing car rentals with a **file-based storage system (CSV)**.
Built with an **OOP + MVC architecture**, it provides full CRUD operations, validation, reporting, and a menu-driven interface.

---

## ✨ Features

### 🔑 Core

* CRUD operations for **Cars, Customers, and Bookings**
* File-based persistence (`.csv` files, no database needed)
* Search, filter, and statistics reporting
* Input validation & error handling
* Backup and restore system

### 🚙 Car Management

* Add, update, delete, and search cars
* Track status (Available, Rented, Maintenance, Retired)
* View fleet statistics

### 👤 Customer Management

* Manage customer profiles
* Validate license, email, and phone number
* View booking history

### 📅 Booking Management

* Create and manage bookings
* Auto cost calculation (daily rate × duration)
* Track status (Active, Completed, Cancelled)
* View by customer or car

---

## 🛠️ Technical Overview

* **Language**: C++17
* **Architecture**: MVC + Service Layer
* **Persistence**: CSV-based (cross-platform, no external DB)
* **Dependencies**: Standard Library only

---

## 📂 Project Structure

```
Car Rental System/
├── main.cpp              # Entry point
├── models/               # Car, Customer, Booking
├── services/             # Business logic
├── ui/                   # Menu & console UI
├── database/             # File manager
├── data/                 # CSV data & backups
└── README.md
```

---

## 🚀 Getting Started

### Prerequisites

* C++17 compatible compiler (GCC, Clang, MSVC)

### Build

```bash
# Using g++
g++ -std=c++17 -o CarRentalSystem main.cpp models/*.cpp services/*.cpp ui/*.cpp database/*.cpp
```

### Run

```bash
./CarRentalSystem    # Linux/macOS
CarRentalSystem.exe  # Windows
```

---

## 💾 Data Format (CSV)

**cars.csv**

```csv
ID,Make,Model,Year,Color,LicensePlate,DailyRate,Status
1,Toyota,Camry,2020,Silver,ABC123,50.00,Available
```

**customers.csv**

```csv
ID,FirstName,LastName,Email,Phone,LicenseNumber,LicenseExpiry
1,John,Doe,john@email.com,1234567890,DL123456,2025-12-31
```

**bookings.csv**

```csv
ID,CustomerID,CarID,StartDate,EndDate,TotalCost,Status
1,1,1,2024-01-01,2024-01-05,250.00,Active
```

## 🐛 Troubleshooting

* **Permission errors** → ensure write access to `data/`
* **Data corruption** → restore from `data/backups/`
* **Compile errors** → enable `-std=c++17` and check all `.cpp` files are included

---
