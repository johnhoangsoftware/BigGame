#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<Windows.h>
#include<string>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#include<iostream>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"LTexture.h"
using namespace std;


const int BKGROUND_WIDTH = 1920;
const int BKGROUND_HEIGHT = 3240;

const int SCREEN_WIDTH = 1400-200;
const int SCREEN_HEIGHT = 787-120;
const int SCREEN_BPP = 32;
 // 7 la so PIXEL screen bi day xuong .
const int PIXEL = 7 ;
const int PIXEL_LIM = (2*BKGROUND_HEIGHT/3)%PIXEL ;
const int PIXEL_START = BKGROUND_HEIGHT/3 + (2*BKGROUND_HEIGHT/3)%PIXEL - PIXEL ;


const int MAX_NUMBER_OF_ENEMY = 18;
const int MAX_NUMBER_OF_BOSS = 3;

const SDL_Color textColor = {241, 196, 10}; // fresh orange color

const int KILL_ENEMY_SCORE = 5 ;
const int KILL_BOSS_SCORE = 20 ;
const int GET_BONUS_SCORE = 5 ;
const int GET_BONUS_STAR_SCORE = 10 ;
const int GET_INJURED_SCORE = -10 ;
const int SCORE_WHICH_BOSS_SHOWN = 30 ;
const int LIVES_PLUS_FOR_KILL_BOSS = 2;
const int LIVES_PLUS_FOR_GET_STAR = 1 ;

static SDL_Window* window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *g_background = NULL;
static SDL_Texture *g_gameover = NULL;
static SDL_Texture *g_bkpicture = NULL;
static SDL_Texture *g_intro = NULL;
static SDL_Event g_even;
static SDL_Rect rect_background ;
static SDL_Rect rect_screen ;


//Globally used font
static TTF_Font *gFont = NULL;

static Mix_Music* g_deploy_missile = NULL;
static Mix_Chunk* g_enemy_death = NULL;
static Mix_Chunk* g_bk_music = NULL;
static Mix_Chunk* g_through_gate = NULL;
static Mix_Chunk* g_end_music = NULL;
static Mix_Chunk* g_enemy_bullet = NULL;
static Mix_Chunk* g_get_item  = NULL;
static Mix_Chunk* g_success_get_item = NULL ;
static Mix_Chunk* g_main_injured = NULL;



namespace Common_Function
{
	SDL_Texture * LoadImage (string path, SDL_Renderer *ren);
	void ApplySurface(SDL_Renderer *renderer, SDL_Texture *src, int x, int y, int w, int h);
    void LoadIntro(SDL_Renderer* ren);
    void ShowIntro(SDL_Renderer* ren);
	void CleanUp();
	void LoadBackGround(SDL_Renderer* ren);
	void ShowBackGround(SDL_Renderer* ren);
}

#endif



SDL_Texture * Common_Function::LoadImage(string path, SDL_Renderer *ren) {

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface( ren , loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;

}

void Common_Function::ApplySurface( SDL_Renderer *renderer , SDL_Texture *src, int x, int y, int w, int h) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	offset.h = h;
	offset.w = w;
	SDL_RenderCopy(renderer, src , NULL, &offset);
	SDL_RenderPresent(renderer);
}

void Common_Function::CleanUp() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Common_Function::LoadIntro(SDL_Renderer* ren)
{
    g_intro = Common_Function::LoadImage("gameShooting/intro.png", ren);
}
void Common_Function::ShowIntro(SDL_Renderer* ren)
{
    rect_screen.w = SCREEN_WIDTH ;
	rect_screen.h = SCREEN_HEIGHT ;

    SDL_RenderCopy(ren,g_intro,NULL,&rect_screen);
    SDL_RenderPresent(ren);
}
void Common_Function::LoadBackGround(SDL_Renderer* ren)
{
    g_background = Common_Function::LoadImage("gameShooting/perfectBK.png", ren);

    rect_background.w = BKGROUND_WIDTH ;
    rect_background.h = BKGROUND_HEIGHT/3 ;
    rect_background.x = 0;
    rect_background.y = BKGROUND_HEIGHT/3;

    rect_screen.w = SCREEN_WIDTH;
    rect_screen.h = SCREEN_HEIGHT;
    rect_screen.x = 0;
    rect_screen.y = 0;
}
void Common_Function::ShowBackGround(SDL_Renderer* ren)
{
	SDL_RenderCopy(ren,g_background,&rect_background,&rect_screen);
    SDL_RenderPresent(ren);

    if ( rect_background.y <= PIXEL_LIM ) {
        rect_background.y = PIXEL_START ;
    }
    else {
        rect_background.y-=PIXEL;
    }

}
