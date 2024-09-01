#pragma once
#include <string>

#include "IBookingServiceObserver.h"

namespace booking
{

namespace core
{

class IBookingServiceNotifier
{
public:
    virtual ~IBookingServiceNotifier() = default;

    virtual void Attach(IBookingServiceObserver *observer) = 0;
    virtual void Detach(IBookingServiceObserver *observer) = 0;

    virtual void NotifyOnRequestUpdate(IBookingServiceObserver* observer, std::string& row, unsigned char seat, int error) = 0;
    virtual void NotifyOnUpdate(const std::string& theatre, const std::string& movie) = 0;
};

}
}
