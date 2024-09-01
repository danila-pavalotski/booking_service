#pragma once
#include <list>
#include <queue>
#include <mutex>
#include <string>
#include <thread>

#include "data/BookingData.h"
#include "IBookingServiceNotifier.h"
#include "IBookingServiceObserver.h"

/**
 * @file BookingService.h
 * @brief Defines classes and functions for booking service.
 */

/**
 * @class BookingService
 * @brief Provide methods to work with booking service.
 */

namespace booking
{

namespace core
{

class BookingService : public IBookingServiceNotifier
{

private:

    BookingService() = default;
    ~BookingService() = default;

    struct BookingRequest{
        int seat;
        std::string theatre;
        std::string movie;
        std::string row;
        data::BookingData::SEAT status;
        IBookingServiceObserver* client;
    };

    bool m_isStop = true;
    std::mutex m_mutex;
    std::thread m_mainThread;
    booking::data::BookingData m_data;
    std::queue<BookingRequest> m_queueRequests;
    std::list<IBookingServiceObserver *> m_list_observer;

    void mainThread();

    void NotifyOnRequestUpdate(IBookingServiceObserver* observer, std::string& row, unsigned char seat, int error) override;

    void NotifyOnUpdate(const std::string& theatre, const std::string& movie) override;

public:

    /**
     * @brief BookingService constructor (singleton).
     * @details Construct object to BookingService.
     * @return BookingService Instance of BookingService.
     */
    static BookingService& getInstance() {
        static BookingService instance;
        return instance;
    }

    /**
     * @brief Start BookingService.
     * @details The method starts BookingService.
     * @return int 0 - succesful, -1 - error.
     */
    int Run();

    /**
     * @brief Stop BookingService.
     * @details The method stops BookingService.
     * @return int 0 - succesful, -1 - error.
     */
    int Stop();

    void Attach(IBookingServiceObserver *observer) override;

    void Detach(IBookingServiceObserver *observer) override;

    std::vector<std::string> GetAllMovies();

    std::vector<std::string> GetAllTheatres();

    std::vector<std::string> GetAllMoviesByTheatre(std::string theatre);

    std::vector<std::string> GetAllTheatresByMovie(std::string movie);

    std::map<std::string, std::vector<int>> GetAllSeats(std::string theatre, std::string movie);

    void MakeBookRequest(std::string theatre, std::string movie, std::string row, unsigned char seat);

    void MakeBookRequest(IBookingServiceObserver* observer, std::string theatre, std::string movie, std::string row, unsigned char seat);

};
}
}
