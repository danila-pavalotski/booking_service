#pragma once
#include <string>

/**
 * @file IBookingObserver.h
 * @brief Defines interface for BookingRequestModel.
 */

/**
 * @class IBookingObserver
 * @brief Implements interface IBookingObserver.
 */

namespace booking
{
namespace api
{

class IBookingObserver
{
public:
    virtual ~IBookingObserver() = default;

    /**
     * @brief Request feedback.
     * @details The method receives feedback for the request.
     * @param row Requested row
     * @param seat Requester seat
     * @param error 0 - success, -1 - error
     */
    virtual void OnRequestUpdate(std::string row, unsigned char seat, int error) = 0;

    /**
     * @brief Notify about updates.
     * @details The method notified all observers that was attached that there are updated with theatre/movie.
     * @param theatre Updates connected with that theatre
     * @param movie Updates connected with that movie
     */
    virtual void OnUpdate(std::string theatre, std::string movie) = 0;
};

}
}
