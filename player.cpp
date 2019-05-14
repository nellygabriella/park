#include "player.h"

player::player(const char* n, collisionsphere ccs, float sprints, float normals, float looks)
{
    name=n;
    cs=ccs;
    sprintspeed=sprints;
    normalspeed=normals;
    lookspeed=looks;
    force.change(0.0,-0.3,0.0);
    direction.change(0.0,0.0,0.0);
    setPosition(vector3d(0.0,3,0.0));
    cam.setSpeed(normalspeed,looks);
    isground=iscollision=issprint=false;
}

void player::setPosition(vector3d pos)
{
    cs.center=pos;
    cam.setLocation(pos);
}

collisionsphere player::getCollisionSphere()
{
    return cs;
}

player::~player()
{

}

void player::update(std::vector<collisionplane>& collplane)
{
    if(direction.y<=force.y)
		direction+=force;
    //setPosition(direction);
    vector3d newpos(cam.getLocation());
    newpos+=direction;
    vector3d tmp(newpos);
    for(std::size_t i=0;i<collplane.size();i++)
        collision::sphereplane(newpos,collplane[i].normal,collplane[i].p[0],collplane[i].p[1],collplane[i].p[2],collplane[i].p[3],cs.r);
    if(newpos.y>tmp.y)
        isground=true;
    else
        isground=false;
    setPosition(newpos);
}

std::string player::getName()
{
    return name;
}

void player::show()
{

}
