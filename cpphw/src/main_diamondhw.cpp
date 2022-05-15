#include <string>
#include <iostream>

using namespace std;

/*
idea:
            Camera
            /     \
           /       \
         Lens      Body
            \       /
             \     /
               DSLR
*/


struct Camera
{
    private: char m_multicamLabel; //a cam, b cam, c cam, etc.
    //used when there are multiple cameras in a production. EX: a cam speeding, b cam cut, etc.
    public: 
        Camera()
        {
            cout << "Camera()" << endl;
        }
    virtual char Cbrand() const {return m_multicamLabel;}
    virtual void Cbrand(const char &value) {m_multicamLabel = value;}
    virtual ~Camera() { cout << "~Camera()" << endl;}
};

struct Body;
struct Lens;

struct Body: virtual Camera
{
    const string brand;
    //const int focalLength;
    //Body(string _mount, int _focalLength) : mount(_mount), focalLength(_focalLength) { cout << "Body" << endl;}
    Body(string _brand) : brand(_brand) { cout << "Body" << endl;}

    virtual bool lensAttached(const ConnectedLens &connectedlens) const;
    virtual ~Body() { cout << "~Body()" << endl;}
};

struct ConnectedLens : virtual Camera
{
    const bool lensPowered;
    ConnectedLens(bool _lensPowered) : lensPowered(_lensPowered) {}
};

bool Body::lensAttached(const ConnectedLens &connectedlens) const
{
    cout << "Body::lensAttached()" << endl;
    return connectedlens.lensPowered;
}


struct Lens : virtual Camera
{
    bool mounted;
    Lens() : mounted(true) { cout << "ConnectedLens" << endl;}
    virtual void error() {mounted = false;}
    virtual void reset() {mounted = true;}

    virtual ~Lens(){cout << "~ConnectedLens()" << endl;}
};


struct DSLR : Body, Lens, virtual Camera
{
    DSLR(string brand) : Body(brand) { cout << "DSLR" << endl;}
    virtual bool lensAttached(const ConnectedLens &connectedlens) const override
    {
        cout << "DSLR::lensAttached()" << endl;
        if(!mounted) return false;
        return Body::lensAttached(connectedlens);
    }
    ~DSLR() {cout << "~DSLR" << endl;}
};

int main(int argc, const char *argv[])
{
    DSLR myDSLR("ef");
}