#ifndef COLLISIONSPHERE_H_INCLUDED
#define COLLISIONSPHERE_H_INCLUDED
#include "vector3d.h"

class collisionsphere{
    public:
        float r;
        vector3d center;
        collisionsphere();
        collisionsphere(const vector3d& vec,float rad);

};

#endif // COLLISIONSPHERE_H_INCLUDED
