#pragma once
#include <string>

namespace booking
{

namespace core
{

class IBookingServiceObserver
{
public:
    virtual ~IBookingServiceObserver() = default;

    virtual void OnRequestUpdate(std::string row, unsigned char seat, int error) = 0;
    virtual void OnUpdate(std::string theatre, std::string movie) = 0;
};

}
}
