#ifndef MENU_H
#define MENU_H

#include "RunFunction.h"
#include "Variable.h"
class Menu : public LTexture
{
public:
    Menu();
    ~Menu();

    void loadIntroGame( SDL_Event &e);
    void loadOutroGame( SDL_Event &e);
    bool getis_Play(){return is_Play;};
    bool getexit_Menu(){return exit_Menu;};


private:
    bool exit_Menu;
    bool is_Play;
    int xMouse;
    int yMouse;
};

Menu::Menu()
{
    exit_Menu = false;
    is_Play = false;
    xMouse = 0;
    yMouse = 0;
}

Menu::~Menu()
{

}

void Menu::loadIntroGame(SDL_Event &e)
{
    Mix_PlayMusic(g_Sound_Menu,-1);

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
    gBackgroundMenu.setWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT-300);
    gBackgroundMenu.render(0,0);
    for(int i = 0; i<3; i++)
    {
        gItemMenu[i].setWidthHeight(200,75);
    }
    gItemMenu[0].render(100,525);
    gItemMenu[2].render(400,525);
    SDL_RenderPresent(gRenderer);
    while(!exit_Menu)
    {


        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT|| e.key.keysym.sym == SDLK_ESCAPE)
            {
                is_Play = false;
                exit_Menu = true;
                //break;
            }

            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                xMouse = e.motion.x;
                yMouse = e.motion.y;

                if(100<= xMouse && xMouse <=300)//Play
                {
                    if(525<= yMouse && yMouse <<600)
                    {
                        is_Play = true;
                        exit_Menu = true;
                        //return;
                    }
                }
                if(400<= xMouse && xMouse <=600)//exit
                    if(525<= yMouse && yMouse <<600)
                    {
                        is_Play = false;
                        exit_Menu = true;
                        //return;
                    }

            }
        }//while event
    }//while true
}

void Menu::loadOutroGame(SDL_Event &e)
{
    Mix_PlayMusic(g_Sound_Menu,-1);
    exit_Menu = false;
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );
    gBackgroundOutroMenu.setWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT-300);
    gBackgroundOutroMenu.render(0,0);
    for(int i = 1; i<3; i++)
    {
        gItemMenu[i].setWidthHeight(200,75);
    }
    gItemMenu[1].render(100,525);
    gItemMenu[2].render(400,525);
    SDL_RenderPresent(gRenderer);
    while(!exit_Menu)
    {


        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT|| e.key.keysym.sym == SDLK_ESCAPE)
            {
                is_Play = false;
                exit_Menu = true;
                //break;
            }

            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                xMouse = e.motion.x;
                yMouse = e.motion.y;

                if(100<= xMouse && xMouse <=300)//Play
                {
                    if(525<= yMouse && yMouse <<600)
                    {
                        is_Play = true;
                        exit_Menu = true;
                        //return;
                    }
                }
                if(400<= xMouse && xMouse <=600)//exit
                    if(525<= yMouse && yMouse <<600)
                    {
                        is_Play = false;
                        exit_Menu = true;
                        //return;
                    }
                    if(is_Play==true)
                std::cout << xMouse <<" "<< yMouse<<" "<<is_Play<<std::endl;
            }
        }//while event
    }//while true
}



#endif // MENU_H
