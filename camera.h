#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <cmath>
#include <iostream>
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "vector3d.h"

class camera{
    vector3d loc;
    float camPitch,camYaw;
    float movevel;
    float mousevel;
    bool mi;
    void lockCamera();
    void moveCamera(float dir);
    void moveCamerUp(float dir);
    public:
        camera();
        camera(vector3d loc);
        camera(vector3d loc, float yaw,float pitch);
        camera(vector3d loc, float yaw, float pitch, float mv,float mov);
        void Control();
        void UpdateCamera();
        vector3d getVector();
        vector3d getLocation();
        float getPitch();
        float getYaw();
        float getMovevel();
        float getMousevel();
        bool isMouseIn();

        void setLocation(vector3d vec);
        void lookAt(float pitch, float yaw);
        void mouseIn(bool b);
        void setSpeed(float mv, float mov);
};


#endif // CAMERA_H_INCLUDED
