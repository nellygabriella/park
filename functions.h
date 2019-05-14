#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "objloader.h"
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void drawCube(float size);
void drawSkybox(float size);
void initskybox();
void killskybox();
unsigned int loadTexture(const char*);

#endif // FUNCTIONS_H_INCLUDED
