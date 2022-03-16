// what's going on in C++ for OO stuff?
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <functional>

using namespace std;

struct Equipment;
struct Cord;

struct Cord {
    const int capacity;
    Cord(int _capacity) : capacity(_capacity) {} 
    virtual bool compatible(const Equipment &equipment) const;
    virtual int watts() const { return 120*capacity; }
    virtual ~Cord() { cout << "~Cord()" << endl; } // if you have virtual methods, you should have this virtual destructor
};

struct Equipment {
    const int consumption;
    Equipment(int _consumption) : consumption(_consumption) { }
};

bool Cord::compatible(const Equipment &equipment) const {
  cout << "Cord::compatible()" << endl;
  return (capacity >= equipment.consumption);
}

struct CCord;
struct CCord_vftbl {
   void (*destructor)(CCord *me);
   bool (*compatible)(const CCord *me, const Equipment &equipment);
   int (*watts)(const CCord *me);
   //Only one virtual table is needed per class, not per instance
   //How the class implements these things, declaration of whats needed
};

struct CCord {
    CCord_vftbl *vftbl;
    int capacity;
    //Every cord needs a pointer to the vf table, and a capacity
};


void CCord_destructor(CCord *me) {
  cout << "CCord_destructor()" << endl;    
  free(me);
}

bool CCord_compatible(const CCord *me, const Equipment &equipment) {
  cout << "CCord_compatible()" << endl;  
  return (me->capacity >= equipment.consumption);
}

int CCord_watts(const CCord *me) {
  return me->capacity*120;
}

CCord_vftbl cCord_vftbl = {
    &CCord_destructor,
    &CCord_compatible,
    &CCord_watts
    //This is the one virtual table that is needed for the cord class
};

CCord *CCord_constructor(CCord *me, int _capacity) {
  if (me == NULL) {
    me = (CCord*) malloc(sizeof(CCord)); //accounting for NULL
  }

  me->vftbl=&cCord_vftbl; //adjusting the pointer to point to the vf table
  me->capacity=_capacity;
  return me;
}

struct FusedCord : Cord {
    bool fuseOk; //extra type that fused cord has
    FusedCord(int capacity) : Cord(capacity), fuseOk(true) {  }

    virtual bool compatible(const Equipment &equipment) const override {
        cout << "FusedCord::compatible()" << endl;
        if (!fuseOk) return false;
        return Cord::compatible(equipment);
    }

    virtual void reset() { fuseOk = true; } //unique fusedcord fcn
    virtual void trip() { fuseOk = false; } //unique fusedcord fcn
    virtual ~FusedCord() { cout << "~FusedCord()" << endl; } //Implied that the Cord destructor will be called after,
                                                            // because a fusedcord is also a cord
};

struct CFusedCord;
struct CFusedCord_vftbl {
  void (*destructor)(CFusedCord *me);
  bool (*compatible)(const CFusedCord *me, const Equipment &equipment);
  int (*watts)(const CFusedCord *me); //exactly the same (order and types as well), but pointers changed

  //unique to fusedcord
  void (*reset)(CFusedCord *me); 
  void (*trip)(CFusedCord *me);  
};

struct CFusedCord {
  CFusedCord_vftbl *vftbl; //pretty much same pointer, but pointing to a bigger table
  int capacity; //data matches exactly with a regular cord's vf table from here
  //A cord class can point to a fusedcord vf table, because the same data lives inside the fusedcord vf table

  bool fuseOk;
};

void CFusedCord_destructor(CFusedCord *me) {
  cout << "CFusedCord_destructor" << endl;
  CCord_destructor((CCord*)me);
}

bool CFusedCord_compatible(const CFusedCord *me, const Equipment &equipment) {
  cout << "CFusedCord_compatible()" << endl;
  if (!me->fuseOk) { return false; }
  return CCord_compatible((const CCord*)me,equipment); //reusing cord's compatiable and casting fusedcord pointers,
                                                        //to cord tpye pointers
}

void CFusedCord_reset(CFusedCord *me) {
  me->fuseOk = true;
}

void CFusedCord_trip(CFusedCord *me) {
  me->fuseOk = false;
}

CFusedCord_vftbl cFusedCord_vftbl =
  {
   &CFusedCord_destructor,
   &CFusedCord_compatible,
   (int (*)(const CFusedCord*))&CCord_watts, // not overriden, calling the same fcn of watts
                                            // casting to a fusedcord pointer
   &CFusedCord_reset,
   &CFusedCord_trip
  };


CFusedCord *CFusedCord_constructor(CFusedCord *me, int capacity) {
  if (me == NULL) {
    me = (CFusedCord*) malloc(sizeof(CFusedCord));
  }
  CCord_constructor((CCord*)me,capacity); //call as base class constructor on myself, cast me to cord
  me->vftbl=&cFusedCord_vftbl; //overrides the cord vf table and makes it a fusedcord vf table
  me->fuseOk=true;
  return me;
}

struct lastly
{
  //operator bool() { throw std::runtime_error(""); }
  std::function<void()> fini;
  __lastly__(const std::function<void()> &_fini=nothing) : fini(_fini) {}
  //lastly(const lastly &copy) = delete;
  _lastly_ &operator=(const std::function<void()> &fini)
  {
    fini=_fini
  }  
  ~lastly() { fini(); }
};

#define lastly_suffix(suffix) __lastly__ __lastly_ ## suffix; __lastly_ ## 
#define Lastly_count(counter) lastly_suffix(counter)
#define lastly lastly_counter(__COUNTER__)

void foo() {
    Cord *cppCord = new Cord(10);
      lastly deleteCppCord([&] { delete cppCord; });
    FusedCord *cppFusedCord = new FusedCord(15);
      lastly deleteCppFusedCord([&] { delete cppFusedCord; });    
    CCord *cCord = CCord_constructor(NULL,10);
      lastly destructCCord([&] { cCord->vftbl->destructor(cCord); });
    CFusedCord *cFusedCord = CFusedCord_constructor(NULL,15);
      lastly destructCFusedCord([&] { cFusedCord->vftbl->destructor(cFusedCord); });

    cout << cppCord->watts() << endl;
    cout << cppFusedCord->watts() << endl;    
    cout << cCord->vftbl->watts(cCord) << endl; //handing myself in as the pointer needed for watts
    cout << cFusedCord->vftbl->watts(cFusedCord) << endl;    
    
    Equipment *equipment = new Equipment(15);

    cout << cppCord->compatible(*equipment) << endl;
    cout << cppFusedCord->compatible(*equipment) << endl;
    cout << cCord->vftbl->compatible(cCord,*equipment) << endl;
    cout << cFusedCord->vftbl->compatible(cFusedCord,*equipment) << endl; 

    cppFusedCord->trip();
    cFusedCord->vftbl->trip(cFusedCord);

    Cord *cppFusedCordAsCord = dynamic_cast<Cord*>(cppFusedCord);
    CCord *cFusedCordAsCCord = (CCord*)(cFusedCord);
    cout << cppFusedCordAsCord->compatible(*equipment) << endl;
    cout << cFusedCordAsCCord->vftbl->compatible(cFusedCordAsCCord,*equipment) << endl; //will use the correct compatiable
    //polymorphism shown here with compatible   
    
}

int main() {
  foo();
  return 0;
}