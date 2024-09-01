#pragma once
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

namespace booking
{
namespace data
{

class Rows
{
public:
    int a;
    int b;
    int c;
    int d;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Rows,
                                   a,
                                   b,
                                   c,
                                   d)
};

class Theatre
{
public:
    string Name;
    Rows Row;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Theatre,
                                   Name,
                                   Row)
};

}
}
