// what's going on in C++ for 00 stuff
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Equipment;

struct Cord 
{
    int x;
    bool compatiable(Equipment &equipment) { return true; }
    Cord(int _x) : x(_x) {}
};

struct Equipment
{
    bool plugged;
    Equipment() { plugged = false;}
    void plug(Cord &cord)
    {
        if(cord.compatiable(*this))
        {
            plugged = true;
        }
    }
};

bool Cord::compatiable(Equipment &equipment)
{
    if(!equipment.plugged && x != 3)
    {
        // ... 
        return true;
    }
    return false;
}

struct CCord;
struct CCord_vftbl
{
    bool (*compatiable)(CCord *me, Equipment &equipment); //pointer to the cord ('this' pointer)
    void (*destructon)(CCord *me); //clean up
};

struct CCord
{
    CCord_vftbl *vftbl;
    int x;
};

struct CFusedCord
{
    // CFusedCord_vftbl *vftbl;
    int x;
    bool fuseOk;
};

bool CCord_compataible(CCord *me, Equipment &equipment)
{
    if(!equipment.plugged && me->x != 3)
    {
        return true;
    }
    return false;
}

struct FusedCord : Cord
{
    bool fuseOk;
    FusedCord(int x) : Cord(x) { fuseOk = true; }

    // override
    bool compatiable(Equipment &equipment)
    {
        cout << "FusedCord::compatiable()" << endl;
        if (!fuseOk) return false;
        else Cord::compatiable(equipment);
    }
};

bool CFusedCord_compatiable(CFusedCord *me, Equipment &equipment)
{
    if(!me->fuseOk) { return false; }
    CCord_compataible(me, equipment);
}

void CCord_destructor(CCord *me)
{
    free(me);
}

CCord_vftbl cCord_vftbl = 
{
    &CCord_compataible,
    &CCord_destructor
};

CCord *CCordConstructor(int _x)
{
    CCord *me = (CCord*) malloc(sizeof(CCord));

    me->vftbl=&cCord_vftbl;
    me->x=_x;
    return me;
}

void foo()
{
    Cord *cppCord = new Cord(3);
    FusedCord *cppFusedCord = new FusedCord(33);
    CCord *cCord = CCordConstructor(3);

    Equipment *equipment = new Equipment();
    //cout << cppCord->compatiable(*equipment) << endl;
    //cout << dynamic_cast<Cord*>(cppFusedCord)->compatiable(*equipment) << endl;
    cout << dynamic_cast<Cord*>(cppFusedCord)->compatiable(*equipment) << endl;

    cout << cCord->vftbl->compatiable(cCord, *equipment) << endl;

    cout << CCord_compatiable(cCord, *equipment) << endl;
}

int main()
{
    foo();
    return 0;
}