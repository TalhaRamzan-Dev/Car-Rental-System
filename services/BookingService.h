#ifndef BOOKINGSERVICE_H
#define BOOKINGSERVICE_H

#include "../models/Booking.h"
#include <vector>
#include <string>

class BookingService {
private:
    std::string dataFile;
    int nextId;

public:
    BookingService();
    
    // CRUD operations
    bool addBooking(const Booking& booking);
    std::vector<Booking> getAllBookings();
    Booking getBookingById(int bookingId);
    std::vector<Booking> getBookingsByCustomerId(int customerId);
    std::vector<Booking> getBookingsByCarId(int carId);
    bool updateBooking(const Booking& booking);
    bool deleteBooking(int bookingId);
    
    // Utility methods
    bool saveBookings(const std::vector<Booking>& bookings);
    std::vector<Booking> loadBookings();
    int getNextId();
    
private:
    Booking parseBookingFromLine(const std::string& line);
    std::string bookingToCsvLine(const Booking& booking);
    void updateNextId(const std::vector<Booking>& bookings);
};

#endif // BOOKINGSERVICE_H
