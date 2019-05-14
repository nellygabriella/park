#ifndef PARK_H_INCLUDED
#define PARK_H_INCLUDED
#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "objloader.h"
#include "vector3d.h"
#include "collisionplane.h"
#include "collisionsphere.h"
#include "functions.h"
#include "camera.h"
#include "level.h"
#include "player.h"

class park{

    objloader obj;

    std::vector<level*> levels;
    player* player1;

    void update();
    void show();
    unsigned int loadTexture(const char* filename);
    void loadAnimation(std::vector<unsigned int>& anim, std::string filename,int frames);

public:
    park();
    ~park();
    void start();

};

#endif // PARK_H_INCLUDED
