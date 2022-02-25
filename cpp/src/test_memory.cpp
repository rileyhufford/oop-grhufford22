//
//
// [STACK v]
//   [main]
//      [TEST-FusedCord-Ok]
//         - FusedCord (room for Cord + bool)
//         - pFusedCord(64 bit ptr to heap)
//  air
// [HEAP ^] (new/delete) (heap allocated)
//  allocated here (pFusedCord)
// GLOBALS
// CONSTANTS
// CODE/TEXT
//
#include "gtest/gtest.h"

#include "cord.h"
#include <memory>
#include <iostream>


class FusedCord : public power::Cord
{
    private: bool m_fuseOk; //automatic
    private: std::string m_fuseType;

    public: FusedCord(int line, double length, const std::string &connector, double capacity)
        : Cord(line, length, connector, capacity)
    {
        m_fuseOk = true;
        m_fuseType = "funnest type!";
        std::cout << "FusedCord@" << (void*) this <<"from" << m_constructedOn << "constructed." << std::endl;
    }

    public: ~FusedCord()
    {
        std::cout << "FusedCord@" << (void*) this <<"from" << m_constructedOn << "destructed." << std::endl;
    }


    
    // ...

};

// root = a->b->c->d  //ref count is used to clean up b,c,d when deleting a
// a<->b<->c<->d
using namespace power;
using namespace std;
TEST(FusedCord,Ok)
{
    double length = 15.0;
    string connector = "female 3-prong";
    double capacity = 20.0;
    
    
    FusedCord fusedCord(__LINE__, length, connector, capacity); //automatic
    FusedCord *pFusedCord = new FusedCord(__LINE__, length, connector, capacity);
    Cord cord = FusedCord(__LINE__, length, connector, capacity); //compiles but almost certaintly broken (object truncation)

    Cord *pCord = new FusedCord(__LINE__, length, connector, capacity); //better
    // .. delete pCord;
    ASSERT_EQ(cord.length(), length()+1);
    SPCord spCord (new FusedCord(__LINE__, length, connector, capacity)); //correct
    ASSERT_EQ(cord.length(), length +1);

    spCord = SPCord(new FusedCord(__LINE__, length, connector, capacity));

    delete (FusedCord*)pCord;
    close();
    // ...
}