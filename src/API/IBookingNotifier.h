#pragma once
#include <string>

#include "IBookingObserver.h"

/**
 * @file IBookingNotifier.h
 * @brief Defines interface for BookingRequestModel.
 */

/**
 * @class IBookingNotifier
 * @brief Implements interface IBookingNotifier.
 */

namespace booking
{
namespace api
{

class IBookingNotifier
{
public:
    virtual ~IBookingNotifier() = default;

    /**
     * @brief Attach control object.
     * @details The method attaches control object to receive feedback.
     * @param observer Interface class to observe events (Pattern: Observer)
     */
    virtual void Attach(IBookingObserver *observer) = 0;

    /**
     * @brief Detach control object.
     * @details The method dettaches control object to receive feedback.
     * @param observer Interface class to observe events (Pattern: Observer)
     */
    virtual void Detach(IBookingObserver *observer) = 0;

    /**
     * @brief Request feedback.
     * @details The method receives feedback for the request.
     * @param row Requested row
     * @param seat Requester seat
     * @param error 0 - success, -1 - error
     */
    virtual void NotifyOnRequestUpdate(std::string& row, unsigned char seat, int error) = 0;

    /**
     * @brief Notify about updates.
     * @details The method notified all observers that was attached that there are updated with theatre/movie.
     * @param theatre Updates connected with that theatre
     * @param movie Updates connected with that movie
     */
    virtual void NotifyOnUpdate(const std::string& theatre, const std::string& movie) = 0;

};

}
}
