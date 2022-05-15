#pragma once

#include <string>

namespace std
{
    class Camera
    {
        private:
            string m_mount;
            int m_focalLength;

        static int checkFocalLength(int focalLength)
        {
            if(focalLength > 0) return focalLength;
            else throw out_of_range("focal length cannot be zero or less!");
        }

        public:
            Camera(string mount, int focalLength)
                : m_mount(mount), m_focalLength(checkFocalLength(focalLength))
            {}
            Camera(string mount)
                : m_mount(mount)
            {}
            ~Camera(); //destructor
        


        public: 
            //getters
            string mount() const
            {
                return m_mount;
            }
            int CfocalLength() const
            {
                return m_focalLength;
            }
            //setters
            void focalLength(const int &value)
            {
                m_focalLength = checkFocalLength(value);
            }
    };
}