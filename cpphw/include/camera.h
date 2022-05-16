#pragma once

#include <string>
#include <stdexcept>

using namespace std;

    class Camera
    {
        private:
            string m_mount;
            int m_CfocalLength;

        static int checkFocalLength(int CfocalLength)
        {
            if(CfocalLength > 0) return CfocalLength;
            else 
            {
                throw out_of_range("focal length cannot be zero or less!");
            }
        }

        public:
            Camera(string mount, int CfocalLength)
                : m_mount(mount), m_CfocalLength(checkFocalLength(CfocalLength))
            {}
            Camera(string mount)
                : m_mount(mount)
            {}
            ~Camera() = default; //destructor
            
        


        public: 
            //getters
            string mount() const
            {
                return m_mount;
            }
            int CfocalLength() const
            {
                return m_CfocalLength;
            }
            //setters
            void CfocalLength(const int &value)
            {
                m_CfocalLength = checkFocalLength(value);
            }
    };
