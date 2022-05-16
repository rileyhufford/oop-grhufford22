#include <stdexcept>
#include <iomanip>
#include <string>
#include <iostream>
#include "camera.h"

using namespace std;

    struct Lens;
    struct Body;

    struct Lens
    {
        string m_mountType;
        int m_LfocalLength;
        Lens(string _mountType, int _LfocalLength) : m_mountType(_mountType), m_LfocalLength(_LfocalLength) {}
        Lens(int _LfocalLength) : m_LfocalLength(_LfocalLength) {}

        string mountType() const {return m_mountType;}
        int LfocalLength() const {return m_LfocalLength;}
    };

    struct Body : Camera, Lens
    {
        bool m_mirrorless;
        int m_focalLength;
        Body(string _mount, int _focalLength, bool _mirrorless) : Camera(_mount), Lens(_focalLength), m_mirrorless(_mirrorless) {}
        
        bool mirrorless() const {return m_mirrorless;}
    };

    //destructor
    ///Camera::~Camera() = default;



    void foo()
    {
        Camera *cppCamera = new Camera("ef", 50);
        Lens *cppLens = new Lens("ef", 50);
        Body *cppBody = new Body("ef", 50, false);

        cout << "Camera: mount: " << cppCamera->mount() << ", focal length: " << cppCamera->CfocalLength() << endl;
        cout << "Lens: mount: " << cppLens->mountType() << ", focal length: " << cppLens->LfocalLength() << endl;
        cout << "Body: mount: " << cppBody->mount() << ", focal length: " << cppBody->CfocalLength() << 
        ", mirorrless?: " << cppBody->mirrorless() << endl;

        delete cppCamera;
        delete cppLens;
        delete cppBody;
    }


int main()
{
    foo();
    return 0;
}