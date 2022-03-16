#include <string>
#include <iostream>

using namespace std;

struct Device // similar to interface in Java/C#
{
    // its a good idea to only have a default constructor
    private: string m_ip;
    public: Device() { cout << "Device()" << endl; } // default constructor only
    virtual string ip() const { return m_ip; }
    virtual void id(const string &value) { m_ip = value;}
    virtual ~Device() {cout << "~Device()" << endl;}
};

struct Equipment;
struct Cord;

struct Cord : virtual Device{
    const int capacity;
    Cord(int _capacity) : capacity(_capacity) { cout << "Cord()" << endl;} 
    virtual bool compatible(const Equipment &equipment) const;
    virtual int watts() const { return 120*capacity; }
    virtual ~Cord() { cout << "~Cord()" << endl; } // if you have virtual methods, you should have this virtual destructor
};

struct Equipment : virtual Device {
    const int consumption;
    Equipment(int _consumption) : consumption(_consumption) { }
};

bool Cord::compatible(const Equipment &equipment) const {
  cout << "Cord::compatible()" << endl;
  return (capacity >= equipment.consumption);
}

struct Fused : virtual Device{
    bool fuseOk; //extra type that fused cord has
    Fused() : fuseOk(true) { cout << "Fused()" << endl;}

    virtual void reset() { fuseOk = true; } //unique fusedcord fcn
    virtual void trip() { fuseOk = false; } //unique fusedcord fcn
    virtual ~Fused() { cout << "~Fused()" << endl; } //Implied that the Cord destructor will be called after,
                                                            // because a fusedcord is also a cord
};

struct FusedCord : Cord, Fused, virtual Device {
    FusedCord(int capacity) : Cord(capacity) { cout << "FusedCord" << endl;}
    virtual bool compatible(const Equipment &equipment) const override {
        cout << "FusedCord::compatible()" << endl;
        if (!fuseOk) return false;
        return Cord::compatible(equipment);
    }
    ~FusedCord() {cout << "~FusedCord" << endl;}
};


//     Device (virtual base classes)
//    |       \
//  Cord       Fused (fuseOk, trip, reset)
//      \       /
//       \     /
//       FusedCord (ip)

int main(int argc, const char *argv[])
{
    FusedCord fusedCord(15);
}