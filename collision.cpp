#include "collision.h"

bool collision::raysphere(float xc, float yc, float zc, float xd, float yd, float zd, float xs, float ys, float zs, float r, float* dist, vector3d* point)
{
    float b=2*(xd*(xs-xc)+yd*(ys-yc)+zd*(zs-zc));
    float c=xs*xs-2*xs*xc+xc*xc+ys*ys-2*ys*yc+yc*yc+zs*zs-2*zs*zs+zc*zc-r*r;
    float disc=(b*b-4*c);
    if(disc<0)
        return false;
    if(dist!=NULL)
    {
        (*dist)=(-b+disc)/2;
        if(point!=NULL)
        {
            point->x=xs+(*dist)*xd;
            point->y=ys+(*dist)*yd;
            point->z=zs+(*dist)*zd;
        }
    }
    return true;
}

bool collision::rayplane(float nx, float ny, float nz, float xs, float ys, float zs, float xd, float yd, float zd, vector3d p1, vector3d p2, vector3d p3, vector3d p4, float* dist, vector3d* point)
{
    float a=xd*nx+yd*ny+zd*nz;
    if(a==0)
        return false;
    float t=((p1.x*nx+p1.y*ny+p1.z*nz-nx*xs-ny*ys-nz*zs)/a);
    if(t<0)
        return false;
    float x=xs+t*xd;
    float y=ys+t*yd;
    float z=zs+t*zd;
    vector3d cp(x,y,z);

    if(abs(trianglearea(p1,p3,p4)-trianglearea(p1,p4,cp)-trianglearea(p1,p3,cp)-trianglearea(p3,p4,cp))<0.000001 || abs(trianglearea(p1,p2,p3)-trianglearea(p1,p2,cp)-trianglearea(p2,p3,cp)-trianglearea(p1,p3,cp))<0.000001)
    {
        if(dist!=NULL)
        {
            (*dist)=t;
            if(point!=NULL)
            {
                point->x=x;
                point->y=y;
                point->z=z;
            }
        }
        return true;
    }
    return false;
}

float collision::trianglearea(vector3d p1, vector3d p2,vector3d p3)
{
    float a=sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z));
    float b=sqrt((p3.x-p2.x)*(p3.x-p2.x)+(p3.y-p2.y)*(p3.y-p2.y)+(p3.z-p2.z)*(p3.z-p3.z));
    float c=sqrt((p1.x-p3.x)*(p1.x-p3.x)+(p1.y-p3.y)*(p1.y-p3.y)+(p1.z-p3.z)*(p1.z-p3.z));
    float s=(a+b+c)/2;
    return (sqrt(s*((s-a)*(s-b)*(s-c))));
}

bool collision::spheresphere(vector3d& c1,float r1,vector3d c2, float r2)
{
    float dist=pointdistance(c1,c2);
    if(dist<=(r1+r2)*(r1+r2))
    {
        float a=sqrt(dist)-(r1+r2);
        vector3d vec(c2.x-c1.x,c2.y-c1.y,c2.z-c1.z);
        float len=sqrt((vec.x*vec.x+vec.y*vec.y+vec.z*vec.z));
        vec.x/=len;
        vec.y/=len;
        vec.z/=len;
        c1.x=c1.x+vec.x*a;
        c1.y=c1.y+vec.y*a;
        c1.z=c1.z+vec.z*a;
        return 1;
    }
    return 0;
}

float collision::pointdistance(vector3d c1,vector3d c2)
{
    vector3d vec(c2.x-c1.x,c2.y-c1.y,c2.z-c1.z);
    return (vec.x*vec.x+vec.y*vec.y+vec.z*vec.z);
}

bool collision::sphereplane(vector3d& sp, vector3d vn, vector3d p1, vector3d p2, vector3d p3, vector3d p4, float r)
{
    float dist1=0, dist2=0;
    if(rayplane(-vn.x,-vn.y,-vn.z,sp.x,sp.x,sp.z,vn.x,vn.y,vn.z,p1,p2,p3,p4,&dist1) || rayplane(vn.x,vn.y,vn.z,sp.x,sp.y,sp.z,-vn.x,-vn.y,-vn.z,p1,p2,p3,p4,&dist2))
    {
        if(dist1>r || dist2>r)
            return false;
        if(dist1>0)
        {
            sp.x=sp.x-vn.x*(r-dist1);
            sp.y=sp.y-vn.y*(r-dist1);
            sp.z=sp.z-vn.z*(r-dist1);
        }else{

            sp.x=sp.x-vn.x*(r-dist2);
            sp.y=sp.y-vn.y*(r-dist2);
            sp.z=sp.z-vn.z*(r-dist2);

        }
        return 1;
    }
    return 0;
}
