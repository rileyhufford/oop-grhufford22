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
        Camera() {cout << "Camera() constructor" << endl;}
    virtual char multicamLabel() const {return m_multicamLabel;}
    virtual void multicamLabel(const char &value) {m_multicamLabel = value;}
    virtual ~Camera() { cout << "~Camera()" << endl;}
};

struct Body;
struct Lens;

struct ConnectedLens : virtual Camera
{
    bool lensPowered;
    ConnectedLens(bool _lensPowered) : lensPowered(_lensPowered) {cout << "ConnectedLens() constructor" << endl;}
};

struct Body: virtual Camera
{
    const string brand;
    Body(string _brand) : brand(_brand) { cout << "Body() constructor" << endl;}

    virtual bool lensAttached(const ConnectedLens &connectedlens) const;
    virtual ~Body() { cout << "~Body()" << endl;}
};



bool Body::lensAttached(const ConnectedLens &connectedlens) const{
    cout << "Body::lensAttached()" << endl;
    return (connectedlens.lensPowered);
}


struct Lens : virtual Camera
{
    bool mounted;
    Lens() : mounted(true) { cout << "Lens() constructor" << endl;}
    virtual void error() {mounted = false;}
    virtual void reset() {mounted = true;}

    virtual ~Lens(){cout << "~Lens()" << endl;}
};


struct DSLR : Body, Lens, virtual Camera
{
    DSLR(string brand) : Body(brand) { cout << "DSLR() constructor" << endl;}
    virtual bool lensAttached(const ConnectedLens &connectedlens) const{
        cout << "DSLR::lensAttached()" << endl;
        if(!mounted) return false;
        return Body::lensAttached(connectedlens);
    }
    ~DSLR() {cout << "~DSLR()" << endl;}
};

void foo()
{
    bool lenspowered = true;
    char multicamlabel = 'a';

    DSLR dslr("Canon");
    ConnectedLens connectedlens(lenspowered);

    dslr.lensAttached(connectedlens);
    dslr.multicamLabel(multicamlabel);

    cout << endl << "multicamLabel test(should be 'a'): " << dslr.multicamLabel() << endl << endl;
}

int main()
{
    foo();
    return 0;
}