#ifndef RUNFUNCTION_H
#define RUNFUNCTION_H

#include "Variable.h"
#include "LTexture.h"
#include "Bullet.h"
#include "Threats.h"

//TEXTURE
LTexture gText;
LTexture gBullet;
LTexture gBackground;
LTexture gAircraft;
LTexture gBoom;
LTexture gBackgroundMenu;
LTexture gBackgroundOutroMenu;
LTexture gItemMenu[3];
SDL_Rect gBoomClip[FRAME];



bool CheckCollision(const int &KT , const int &x,const int &y, const int &z, const int &t );

bool init();//Starts up SDL and creates window

bool loadMedia();//Loads media

void close();//Frees media and shuts down SDL


bool CheckCollision(const int &KT , const int &x,const int &y, const int &z, const int &t )
{

    int left_a = x;
  int right_a  ;
  int top_a = y;
  int bottom_a  ;

  int left_b = z;
  int right_b ;
  int top_b = t ;
  int bottom_b ;
  if(KT == 0)// player and threats
    {
        right_a = x + WIDTH_AIRCRAFT-10;
        bottom_a = y+ HEIGHT_AIRCRAFT ;
        right_b = z + WIDTH_AIRCRAFT-10;
        bottom_b = t + HEIGHT_AIRCRAFT;
    }
    else if(KT == 1)// bullet player va threat
    {
        right_a = x +WIDTH_SPHERE ;
        bottom_a = y+HEIGHT_SPHERE ;
        right_b = z + WIDTH_AIRCRAFT-10;
        bottom_b = t + HEIGHT_AIRCRAFT;
    }
    else if(KT == -1) //bullet threats and player
    {
        right_a = x + WIDTH_SPHERE;
        bottom_a = y+ HEIGHT_SPHERE ;
        right_b = z + WIDTH_AIRCRAFT-10;
        bottom_b = t + HEIGHT_AIRCRAFT;
    }
   // SDL_Delay(100);

   // std::cout<< left_a<<" "<<right_a<<" "<<top_a<<" "<<bottom_a<<" "<<left_b<<" "<<right_b<<" "<<top_b<<" "<<bottom_b<<std::endl;
/*
    if(left_a > right_b|| right_a <left_b || bottom_a > top_b || top_a< bottom_b)
        {return false;}
    return true;
*/
//1
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
//TH2
  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }
//TH3
  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }
//TH4
  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

//TH5
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
//TH6
  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }
//TH7
  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }
//TH8
  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

//TH9
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;

}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Game by Hoang", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
				if ( Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1 )
                {
                    printf( " Mix_OpenAudio didn't work !! %s\n" );
                    return false;
                }
                if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if(!gBackgroundMenu.loadFromFile("BackgroundMenu.jpg"))
    {
        printf( "Failed to load background menu texture!\n"  );
		success = false;
    }

    if(!gBackgroundOutroMenu.loadFromFile("BackgroundOutroMenu.jpg"))
    {
        printf( "Failed to load background outro menu texture!\n"  );
		success = false;
    }

	if(!gItemMenu[0].loadFromFile("Play.jpg")||!gItemMenu[1].loadFromFile("Again.jpg")||!gItemMenu[2].loadFromFile("Exit.jpg"))
    {
        printf("Failed to load button menu texture!\n");
        success = false;
    }


	if( !gBackground.loadFromFile("perfectBK.png" ) )//"background1.jpg"
	{
		printf( "Failed to load background texture!\n"  );
		success = false;
	}

	if( !gAircraft.loadFromFile( "Aircraft0.png" ) )
	{
		printf( "Failed to load Aircraft texture!\n", IMG_GetError() );
		success = false;
	}
/*
    if( !gBullet.loadFromFile("background.bmp"))
    {
        printf( "Failed to load Bullet texture!\n", IMG_GetError() );
		success = false;
    }
*/
    if( !gBoom.loadFromFile( "effectbroken0.png" ) )
	{
		printf( "Failed to load effectbroken texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gBoomClip[ 0 ].x =  0;
		gBoomClip[ 0 ].y =  20;
		gBoomClip[ 0 ].w = 100;
		gBoomClip[ 0 ].h = 90;

		gBoomClip[ 1 ].x = 100;
		gBoomClip[ 1 ].y =   20;
		gBoomClip[ 1 ].w = 100;
		gBoomClip[ 1 ].h = 90;

		gBoomClip[ 2 ].x = 200;
		gBoomClip[ 2 ].y = 20;
		gBoomClip[ 2 ].w = 100;
		gBoomClip[ 2 ].h = 90;

		gBoomClip[ 3 ].x = 300;
		gBoomClip[ 3 ].y = 20;
		gBoomClip[ 3 ].w = 100;
		gBoomClip[ 3 ].h = 90;

		gBoomClip[ 4 ].x = 0;
		gBoomClip[ 4 ].y = 150;
		gBoomClip[ 4 ].w = 100;
		gBoomClip[ 4 ].h = 90;

		gBoomClip[ 5 ].x = 105;
		gBoomClip[ 5 ].y = 150;
		gBoomClip[ 5 ].w = 100;
		gBoomClip[ 5 ].h = 90;

		gBoomClip[ 6 ].x = 210;
		gBoomClip[ 6 ].y =   150;
		gBoomClip[ 6 ].w = 100;
		gBoomClip[ 6 ].h = 90;

		gBoomClip[ 7 ].x = 315;
		gBoomClip[ 7 ].y =   150;
		gBoomClip[ 7 ].w = 100;
		gBoomClip[ 7 ].h = 90;

	}


    g_Sound_Background = Mix_LoadMUS("SoundBackground0.wav");
    g_Sound_Broken = Mix_LoadWAV("SoundBroken.wav");
    g_Sound_Bullet = Mix_LoadWAV("SoundBulletSphere.mp3");
    g_Sound_Menu = Mix_LoadMUS("SoundBackground.mp3");
    g_Sound_Laser = Mix_LoadWAV("SoundBulletLaser.mp3");
    if(g_Sound_Background== NULL)
        {
            printf("Don't load sound \n");
            success = false;
        }

    //Open the font
	gFont = TTF_OpenFont( "BodoniFLF-Bold.ttf", 20 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{/*
		//Render the prompt
		SDL_Color textColor = { 255, 255, 255, 0xFF };
		std::string Text = "Some Text";
		if(!gText.loadFromRenderedText(Text.c_str(), textColor) )
		{
			printf( "Failed to render prompt text!\n" );
			success = false;
		}
		*/
	}
	return success;
}

void close()
{
	//Free loaded images
	gBackground.free();
	gBullet.free();
    gAircraft.free();
    gBoom.free();
    gText.free();
    gBackgroundMenu.free();
    gBackgroundOutroMenu.free();
    for(int i = 0; i<4; i++)
    {
        gItemMenu[i].free();
    }
	//Destroy window and renderer
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

}



#endif // RUNFUNCTION_H
