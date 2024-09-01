#include <stdio.h>
#include <API/BookingRequestModel.h>
#include <core/BookingService.h>

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}


int main(int, char**){

    booking::core::BookingService& service = booking::core::BookingService::getInstance();
    service.Run();

    booking::api::BookingRequestModel api;

    std::string command;
    std::cout << "Welcome to the Bookin Service CLI!\n";
    std::cout << "Type 'help' to see the list of commands.\n";

    while(true){
        std::cout << "> ";
        std::getline(std::cin, command);


        std::vector<std::string> tokens = splitString(command, ' ');

        if (command == "exit") {
            break;
        }else if(tokens[0] == "help"){
            std::cout << "Commands:\n";
                        std::cout << "  list_movies - List all movies.\n";
                        std::cout << "  list_theatres - List all theatres.\n";
                        std::cout << "  list_seats <theatre> <movie> - List all seats for a movie in a theatre.\n";
                        std::cout << "  book_seat <theatre> <movie> <row> <seat> - Book a specific seat.\n";
                        std::cout << "  exit - Exit the application.\n";
        }else if(tokens[0] == "list_movies"){

           std::vector<std::string> m;

           if(tokens.size()>1 && tokens[1] == "-t"){
               m = api.ListAllMoviesByTheatre(tokens[2]);
           }else{
               m = api.ListAllMovies();
           }

           for(auto& movie : m){
                std::cout << " - " << movie << std::endl;
           }

        }else if(tokens[0] == "list_theatres"){
            std::vector<std::string> t;

            if(tokens.size()>1 && tokens[1] == "-m"){
                t = api.ListAllTheatresByMovie(tokens[2]);
            }else{
                t= api.ListAllTheatres();
            }

            for(auto& theatre : t){
                 std::cout << " - " << theatre << std::endl;
            }
        }else if(tokens[0] == "list_seats"){
            if(tokens.size() != 3) continue;
            std::map<std::string, std::vector<int>> s = api.ListAllSeats(tokens[1], tokens[2]);

            for(auto& row : s){
                std::cout << "|" <<row.first << "| : ";
                for (auto& n : row.second){
                    std::cout << n << " : ";
                }
                std::cout << endl;
            }
        }else if(tokens[0] == "book_seat"){
            if(tokens.size() != 5) continue;
            api.BookSeat(tokens[1], tokens[2], tokens[3], stoi(tokens[4]));
        }

    }

    return 0;
}
