#ifndef BOOKING_UI_H
#define BOOKING_UI_H

#include "../models/Booking.h"
#include "../services/BookingService.h"
#include "../services/CarService.h"
#include "../services/CustomerService.h"
#include "Menu.h"
#include <vector>

class BookingUI {
private:
    BookingService bookingService;
    CarService carService;
    CustomerService customerService;

public:
    BookingUI();
    
    void showMainMenu();
    void addBooking();
    void viewAllBookings();
    void viewBookingById();
    void viewBookingsByCustomer();
    void viewBookingsByCar();
    void updateBooking();
    void deleteBooking();
    void viewActiveBookings();
    
private:
    void displayBooking(const Booking& booking);
    void displayBookings(const std::vector<Booking>& bookings);
    Booking createBookingFromInput();
    void updateBookingFromInput(Booking& booking);
    void displayCarSelection();
    void displayCustomerSelection();
};

#endif // BOOKING_UI_H
