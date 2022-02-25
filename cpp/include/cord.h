#pragma once // used so that this header file is only accessed once

#include <string>
#include <memory>
//using namespace std, not using this because std is a large library and forces other users to use it
//this is a concern in header files as their can be library conflicts

namespace power
{
    class Cord
    {
        public: const int m_constructedOn;
        //default private, while type struct is default public
        private: double m_length;
        private: std::string m_connector;
        private: double m_capacity;

        public: Cord(int constructedOn, double length, const std::string &connector, double capacity); //constructor

        public: double length() const; //pretty much a getter, but literally a method that returns a double
        public: void length( double value); //pretty much a setter, but literally a method

        //destructor '~' is the cpp identifier
        public: ~Cord();

    };
    typedef std::shared_ptr < Cord > SPCord;

}
