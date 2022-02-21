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

#include "cord.h"

class FusedCord : public power::Cord
{
    private: m_fuseOk; //automatic
    // ...

};

using namespace power;
TEST(FusedCord, Ok)
{
    FusedCord fusedCord; //automatic
    FusedCord *pFusedCord = new FusedCord();
    Cord cord = FusedCord(); //compiles but almost certaintly broken (object truncation)

    Cord *pCord = new FusedCord(); //better
    // .. delete pCord;
    SPCord spCord (new FusedCord()); //correct

    spCord ->length();
    // ...
}