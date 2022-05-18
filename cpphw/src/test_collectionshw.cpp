#include "gtest/gtest.h"
#include <list>
#include <vector>
#include <set>
#include <algorithm>
#include <compare>
#include <map>
#include <stdint.h>
#include <map>



using namespace std;
/*
Camera
    int focal length
    string mount
    bool connects
Lens : Camera
    bool lensPowered
    lensPowered && mount === oppositeMount
LensSort //sort by focalLength

**objects go into the set**

**shared pointers go into the vector**

*/

struct Camera
{
    int focalLength;
    string mount;
    Camera(const string &_mount, int _focalLength) : 
    mount(_mount), focalLength(_focalLength) {};

    virtual bool connected(const string &oppositeMount) const
    {
        return mount == oppositeMount;
    }
};

struct Lens : Camera
{
    bool lensPowered;

    Lens(const string &_mount, int _focalLength) : 
    Camera(_mount, _focalLength), lensPowered(true) {} 

    virtual bool connected(const string &oppositeMount) const override
    {
        return lensPowered && (mount == oppositeMount);
    }
};

typedef list <string> Strings;

bool CameraSort(const Camera &a, const Camera &b)
{
    return a.focalLength < b.focalLength;
}

strong_ordering operator<=>(const Camera &a, const Camera &b) {
  if (a.mount != b.mount) return a.mount <=> b.mount;
  return a.focalLength <=> b.focalLength;
}


ostream& operator<<(ostream &out, const Camera &camera)
{
    return (((((out << "A camera with a ") << camera.focalLength) <<
     "mm lens, with an ") << camera.mount) << " mount");
}



TEST(vector, strings)
{
    Strings a(24);
    vector < Camera > cameras(6, Camera("ef", 24));

    a.push_back("thing");
    a.sort();

    Strings::iterator i = find(a.begin(), a.end(), "thing");

    int direction = 1;

    sort(cameras.begin(), cameras.end(), [direction](auto x, auto y)
    {return direction*x.focalLength < direction*y.focalLength;});

    auto j = find(a.begin(), a.end(), "thing");
}

TEST(vector, hierarchy)
{
    vector<shared_ptr<Camera> > cameras;

    cameras.push_back(shared_ptr<Camera>(new Camera("ef", 50)));
    cameras.push_back(shared_ptr<Camera>(new Lens("ef", 50)));
    cameras.push_back(shared_ptr<Camera>(new Camera("e-mount", 24)));
    cameras.push_back(shared_ptr<Camera>(new Lens("e-mount", 30)));


    for(auto &camera1 : cameras)
    {
        for (auto &camera2 : cameras)
        {
            cout << camera1->connected(camera2->mount);
        }
        cout << endl;
    }

    dynamic_cast<Lens&>(*cameras[1]).lensPowered = false;



    for(auto &camera1 : cameras)
    {
        for(auto &camera2 : cameras)
        {
            cout << camera1->connected(camera2->mount);
        }
        cout << endl;
    }
}

TEST(set, camera)
{
    set<Camera> cameras;
    cameras.insert(Camera("ef", 24));
    cameras.insert(Camera("ef-s", 24));
    cameras.insert(Camera("ef", 50));
    cameras.insert(Camera("rf", 100));
    cameras.insert(Camera("e-mount", 14));
    cameras.insert(Camera("a-mount", 85));

    for (auto& camera : cameras) 
    {
        cout << camera << endl;
    }
}