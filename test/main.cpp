#include <stdio.h>
#include <API/BookingRequestModel.h>
#include <core/BookingService.h>

int main(int, char**){

    booking::core::BookingService& service = booking::core::BookingService::getInstance();
    service.Run();

    booking::api::BookingRequestModel api;

    booking::api::BookingRequestModel api2;
    api.BookSeat("Vox Cinema", "Interstellar", "a", 3);
    api2.BookSeat("Vox Cinema", "Interstellar", "a", 4);
    //service.MakeBookRequest("Vox Cinema", "Interstellar", "a", 3);

    std::string command;
    std::cout << "Welcome to the Movie Ticket Booking System CLI!\n";
    std::cout << "Type 'help' to see the list of commands.\n";

    while(true){
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }else if(command == "help"){
            std::cout << "Commands:\n";
                        std::cout << "  list_movies - List all movies.\n";
                        std::cout << "  list_theatres - List all theatres.\n";
                        std::cout << "  list_seats <theatre> <movie> - List all seats for a movie in a theatre.\n";
                        std::cout << "  book_seat <theatre> <movie> <row> <seat> - Book a specific seat.\n";
                        std::cout << "  exit - Exit the application.\n";
        }


    }

    return 0;
}
