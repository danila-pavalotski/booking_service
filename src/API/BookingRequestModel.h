#pragma once
#include <map>
#include <list>
#include <string>
#include <vector>

#include "IBookingNotifier.h"
#include "IBookingObserver.h"
#include "core/IBookingServiceObserver.h"

/**
 * @file bookingapi.h
 * @brief Defines classes and functions for booking API.
 */

/**
 * @class BookingAPI
 * @brief Provide methods to work with booking service.
 */

namespace booking
{
namespace api
{

class BookingRequestModel : IBookingNotifier, core::IBookingServiceObserver
{

private:
    std::list<IBookingObserver *> m_list_observer;

    void NotifyOnRequestUpdate(std::string& row, unsigned char seat, int error) override;

    void NotifyOnUpdate(const std::string& theatre, const std::string& movie) override;

    void OnRequestUpdate(std::string row, unsigned char seat, int error) override;

    void OnUpdate(std::string theatre, std::string movie) override;

public:

    /**
     * @brief BookingRequestModel constructor.
     * @details Construc object to provide messaging with booking service.
     */
    BookingRequestModel();

    /**
     * @brief BookingRequestModel destructor.
     * @details Destroy object to provide messaging with booking service.
     */
    ~BookingRequestModel();

    /**
     * @brief Attach control object.
     * @details The method attaches control object to receive feedback.
     * @param observer Interface class to observe events (Pattern: Observer)
     */
    void Attach(IBookingObserver *observer) override;

    /**
     * @brief Detach control object.
     * @details The method dettaches control object to receive feedback.
     * @param observer Interface class to observe events (Pattern: Observer)
     */
    void Detach(IBookingObserver *observer) override;

    /**
     * @brief List all available movies.
     * @details The method returns list of all available movies from movies.json file.
     * @return std::vector<std::string> where std::string is name of a movie.
     */
    std::vector<std::string> ListAllMovies();

    /**
     * @brief List all movies that are playing in thatre.
     * @details The method returns list of all available movies in that theatre.
     * @param value std::string of the name of a theatre.
     * @return std::vector<std::string> where std::string is name of a movie.
     */
    std::vector<std::string> ListAllMoviesByTheatre(std::string value);

    /**
     * @brief List all available theatres.
     * @details The method returns list of all available theatres from theatres.json file.
     * @return std::vector<std::string> where std::string is name of a theatre.
     */
    std::vector<std::string> ListAllTheatres();

    /**
     * @brief List all theatres that show a movie.
     * @details The method returns list of all available theatres that show a movie.
     * @param value std::str.,ing of the name of a movie.
     * @return std::vector<std::string> where std::string is name of a theatre.
     */
    std::vector<std::string> ListAllTheatresByMovie(std::string value);

    /**
     * @brief List all seats that theatre have for a movie.
     * @details The method returns list of all seats (free, booked and processing) a movie in a theatre.
     * @param theatre std::string of the name of a theatre.
     * @param movie std::string of the name of a movie.
     * @return std::map<std::string, std::vector<int>>
     *
     * where std::string is name of a raw (a, b and etc).
     * where std::vector<int> is array with size ot total seats for a row.
     * Value 0 means free to book.
     * Value 1 means that already booked
     * Value 2 means that that seat under processing (example, another client is choosing seats)
     */
    std::map<std::string, std::vector<int>> ListAllSeats(std::string theatre, std::string movie);

    /**
     * @brief Book a thetre's seat.
     * @details The method books a theatre's seat.
     * @param theatre std::string of the name of a theatre.
     * @param movie std::string of the name of a movie.
     * @param row std::string of the name of a row.
     * @param seat int of the number of a seat.
     */
    void BookSeat(std::string theatre, std::string movie, std::string row, int seat);

};

}
}
