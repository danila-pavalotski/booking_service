#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

namespace booking
{
namespace data
{

class Movie
{
public:
    string Name;
    vector<string> Theatres;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Movie,
                                   Name,
                                   Theatres)

};

}
}
