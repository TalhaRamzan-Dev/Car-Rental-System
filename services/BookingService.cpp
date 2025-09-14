#include "BookingService.h"
#include <fstream>
#include <sstream>
#include <algorithm>

BookingService::BookingService() : dataFile("data/bookings.csv"), nextId(1) {
    loadBookings();
}

bool BookingService::addBooking(const Booking& booking) {
    std::vector<Booking> bookings = loadBookings();
    Booking newBooking = booking;
    newBooking.setBookingId(getNextId());
    bookings.push_back(newBooking);
    nextId++;
    return saveBookings(bookings);
}

std::vector<Booking> BookingService::getAllBookings() {
    return loadBookings();
}

Booking BookingService::getBookingById(int bookingId) {
    std::vector<Booking> bookings = loadBookings();
    for (const auto& booking : bookings) {
        if (booking.getBookingId() == bookingId) {
            return booking;
        }
    }
    return Booking();
}

std::vector<Booking> BookingService::getBookingsByCustomerId(int customerId) {
    std::vector<Booking> bookings = loadBookings();
    std::vector<Booking> results;
    for (const auto& booking : bookings) {
        if (booking.getCustomerId() == customerId) {
            results.push_back(booking);
        }
    }
    return results;
}

std::vector<Booking> BookingService::getBookingsByCarId(int carId) {
    std::vector<Booking> bookings = loadBookings();
    std::vector<Booking> results;
    for (const auto& booking : bookings) {
        if (booking.getCarId() == carId) {
            results.push_back(booking);
        }
    }
    return results;
}

bool BookingService::updateBooking(const Booking& booking) {
    std::vector<Booking> bookings = loadBookings();
    for (auto& b : bookings) {
        if (b.getBookingId() == booking.getBookingId()) {
            b = booking;
            return saveBookings(bookings);
        }
    }
    return false;
}

bool BookingService::deleteBooking(int bookingId) {
    std::vector<Booking> bookings = loadBookings();
    auto it = std::remove_if(bookings.begin(), bookings.end(),
        [bookingId](const Booking& booking) { return booking.getBookingId() == bookingId; });
    
    if (it != bookings.end()) {
        bookings.erase(it, bookings.end());
        return saveBookings(bookings);
    }
    return false;
}

bool BookingService::saveBookings(const std::vector<Booking>& bookings) {
    std::ofstream file(dataFile);
    if (!file.is_open()) return false;
    
    file << "ID,CustomerID,CarID,StartDate,EndDate,TotalCost,Status,Notes\n";
    for (const auto& booking : bookings) {
        file << bookingToCsvLine(booking) << "\n";
    }
    file.close();
    return true;
}

std::vector<Booking> BookingService::loadBookings() {
    std::vector<Booking> bookings;
    std::ifstream file(dataFile);
    if (!file.is_open()) return bookings;
    
    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (firstLine) { firstLine = false; continue; }
        if (!line.empty()) {
            Booking booking = parseBookingFromLine(line);
            if (booking.getBookingId() > 0) {
                bookings.push_back(booking);
            }
        }
    }
    file.close();
    updateNextId(bookings);
    return bookings;
}

int BookingService::getNextId() { return nextId; }

Booking BookingService::parseBookingFromLine(const std::string& line) {
    Booking booking;
    std::stringstream ss(line);
    std::string field;
    std::vector<std::string> fields;
    
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    
    if (fields.size() >= 7) {
        try {
            booking.setBookingId(std::stoi(fields[0]));
            booking.setCustomerId(std::stoi(fields[1]));
            booking.setCarId(std::stoi(fields[2]));
            booking.setStartDate(fields[3]);
            booking.setEndDate(fields[4]);
            booking.setTotalCost(std::stod(fields[5]));
            booking.setStatus(fields[6]);
            if (fields.size() > 7) {
                booking.setNotes(fields[7]);
            }
        } catch (const std::exception& e) {
            return Booking();
        }
    }
    return booking;
}

std::string BookingService::bookingToCsvLine(const Booking& booking) {
    std::stringstream ss;
    ss << booking.getBookingId() << ","
       << booking.getCustomerId() << ","
       << booking.getCarId() << ","
       << booking.getStartDate() << ","
       << booking.getEndDate() << ","
       << booking.getTotalCost() << ","
       << booking.getStatus() << ","
       << booking.getNotes();
    return ss.str();
}

void BookingService::updateNextId(const std::vector<Booking>& bookings) {
    int maxId = 0;
    for (const auto& booking : bookings) {
        if (booking.getBookingId() > maxId) {
            maxId = booking.getBookingId();
        }
    }
    nextId = maxId + 1;
}
