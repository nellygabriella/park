#include "park.h"


park::park()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen=SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    glClearColor(0.5,0.5,0.5,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    initskybox();
    std::vector<collisionplane> mapcp;
    std::vector<vector3d> mapsp;
    mapsp.push_back(vector3d(3,5,5));
    unsigned int mapa=obj.load("untitled.obj",&mapcp);
    levels.push_back(new level("name",mapa,mapcp,mapsp));
    player1=new player("player1",collisionsphere(vector3d(0,50,30),3.0),0.2,0.2,0.2);


}

park::~park()
{
    for(int i=0;i<levels.size();i++)
        delete levels[i];
    SDL_Quit();
    killskybox();
}

void park::start()
{
    Uint32 start;
    SDL_Event event;
    bool running=true;

    while(running)
    {
        start=SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running=false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    player1->cam.mouseIn(true);
                    SDL_ShowCursor(SDL_DISABLE);
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        running=false;
                        break;
                    }
                    if(event.key.keysym.sym==SDLK_p)
                    {
                        player1->cam.mouseIn(false);
                        SDL_ShowCursor(SDL_ENABLE);
                        break;
                    }
            }
        }

        update();
        show();

        SDL_GL_SwapBuffers();
        if(1000/30>(SDL_GetTicks()-start))
            SDL_Delay(1000/30-(SDL_GetTicks()-start));
    }
}

void park::update()
{
    for(int i=0;i<levels.size();i++)
        levels[i]->update();
    player1->update(levels[0]->getCollisionPlanes());
}

void park::show()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    player1->cam.Control();
    drawSkybox(50.0);
    player1->cam.UpdateCamera();
    for(std::size_t i=0;i<levels.size();i++)
        levels[i]->show();
    player1->show();
        glColor3f(1.0,1.0,1.0);
}
