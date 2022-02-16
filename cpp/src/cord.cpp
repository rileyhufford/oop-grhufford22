#include "cord.h"
#include <stdexcept>

namespace power
{
    static double checkedLength(double length)
    {
        if (length > 0.0)
        {
            return length;
        }
        else
        {
            throw new std::out_of_range("length must be positive");
        }
    }

    Cord::Cord(double length, const std::string &connector, double capacity)
        : m_length(checkedLength(length)), m_connector(connector), m_capacity(capacity) // this is the intializer and you can intialize
                                                                                        // the values you want in them
    {
        //constructor
    }
    double Cord::length() const
    {
        return m_length;
    }
    void Cord::length(double value)
    {
        m_length = checkedLength(value);
    }

}