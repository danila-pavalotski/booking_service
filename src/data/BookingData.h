#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "data/Theatre.h"
#include "data/Movie.h"
#include "data/BookingSeats.h"

namespace fs = std::filesystem;
using namespace std;
using namespace nlohmann;

namespace booking
{
namespace data
{

class BookingData
{

private:
    vector<Movie> m_movies;
    vector<Theatre> m_theatres;
    vector<BookingSeats> m_bookingSeats;

    string m_folderSave = "static";
    string m_moviesFile = "movies.json";
    string m_theatresFile = "theatres.json";
    string m_bookingSeatsFile = "booking_seats.json";

    void FillBookingData();
    stringstream LoadData(string filename);
    bool WriteDataToFile(string filename, json jsonArray);

public:

    enum SEAT{
      FREE       = 0,
      BOOKED     = 1
    };

    BookingData();

    bool LoadTheatresData();

    bool LoadMoviesData();

    bool LoadBookingData();

    SEAT GetSeatStatus(std::string theatre,
                       std::string movie,
                       std::string row,
                       unsigned char seat);

    void SetSeatStatus(std::string theatre,
                       std::string movie,
                       std::string row,
                       unsigned char seat,
                       SEAT status);

    std::vector<std::string> GetAllMovies();

    std::vector<std::string> GetAllTheatres();

    std::vector<std::string> GetAllMoviesByTheatre(std::string theatre);

    std::vector<std::string> GetAllTheatresByMovie(std::string movie);

    const std::vector<BookingSeats>* GetBookingSeats();

};

}
}
