#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;

namespace booking
{
namespace data
{

class BookingMovie
{

public:
    string Name;
    vector<int> a;
    vector<int> b;
    vector<int> c;
    vector<int> d;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(BookingMovie,
                                   Name,
                                   a,
                                   b,
                                   c,
                                   d)
};

class BookingSeats
{

public:

    string Name;
    vector<BookingMovie> Movies;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(BookingSeats,
                                   Name,
                                   Movies)


};

}
}
