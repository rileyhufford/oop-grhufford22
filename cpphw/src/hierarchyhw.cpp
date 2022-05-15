#include <stdexcept>
#include <iomanip>
#include <string>
#include <iostream>

#include "camera.h"

namespace std
{
    struct Lens;
    struct Body;

    struct Lens
    {
        string m_mountType;
        int m_LfocalLength;
        Lens(string _mountType, int _focalLength) : m_mountType(_mountType), m_LfocalLength(_focalLength) {}
        Lens(int _focalLength) : m_LfocalLength(_focalLength) {}

        string mountType() const {return m_mountType;}
        int focalLength() const {return m_LfocalLength;}
    };

    struct Body : Camera, Lens
    {
        bool m_mirrorless;
        int m_focalLength;
        Body(string _mount, int _focalLength, bool _mirrorless) : Camera(_mount), Lens(_focalLength), m_mirrorless(_mirrorless) {}
        
        bool mirrorless() const {return m_mirrorless;}
    };



    void foo()
    {
        Camera *cppCamera = new Camera("ef", 50);
        Lens *cppLens = new Lens("ef", 50);
        Body *cppBody = new Body("ef", 50, false);

        cout << "Camera: mount: " << cppCamera->mount() << ", focal length: " << cppCamera->CfocalLength() << endl;
        cout << "Lens: mount: " << cppLens->mountType() << ", focal length: " << cppLens->focalLength() << endl;
        cout << "Lens: mount: " << cppBody->mount() << ", focal length: " << cppBody->CfocalLength() << 
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
}