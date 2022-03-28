//collections framework
//C++ collections philosophy
//
// 1. C++ makes custom objects for each
// rest in google doc


//vector

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

struct Cord
{
    int length;
    Cord(int _length) : length(_length){};
};

TEST(vector, strings)
{
    std::vector < std::string > a(33); //default constructor creates strings for 2nd arg
    std::vector < Cord > cords(10, Cord(0));

    //Cord cord;

    a.push_back("thing");
    std::sort(a.begin(),a.end());
    std::vector <std::string> :: iterator i = std::find(a.begin(),a.end(), "thing");

    auto j = std::find(a.begin(),a.end(), "thing");
}