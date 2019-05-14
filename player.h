#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <string>
#include "vector3d.h"
#include "collisionplane.h"
#include "collisionsphere.h"
#include "collision.h"
#include "camera.h"

class player{

    std::string name;
    collisionsphere cs;
    vector3d force;
    vector3d direction;
    bool isground,iscollision,issprint;
    float sprintspeed,normalspeed;
    float lookspeed;


    public:
        camera cam;
        player(const char* n, collisionsphere ccs, float sprints, float normals, float looks);
        ~player();
        void update(std::vector<collisionplane>& collplane);
        void show();
        void setPosition(vector3d pos);
        std::string getName();
        collisionsphere getCollisionSphere();

};

#endif // PLAYER_H_INCLUDED
