#include "Menu.h"

using namespace std;

int main( int argc, char* args[] )
{
	int x= SCREEN_WIDTH/2-WIDTH_AIRCRAFT/2;
	int y = SCREEN_HEIGHT-HEIGHT_AIRCRAFT;
	int step = 20;
	int ScrollBG = 3240-SCREEN_HEIGHT;
    int Player_Die = 0;
    Menu gMenu;

	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    SDL_Event e;
            //while(!gMenu.getexit_Menu())
            {
                gMenu.loadIntroGame(e);
            }


			while(gMenu.getis_Play()== true)
            {
                //Main loop flag
                bool quit = false;

                //Event handler
                std::vector<Bullet*> p_bullet_list_;

                // Make Threats
                Threats * p_threat = new Threats[NUMTHREATS];
                for(int i = 0; i < NUMTHREATS; i++){
                    Threats * p_threats = (p_threat+i);
                    if(p_threats)
                    {
                        p_threats -> loadFromFile("Threats0.png");
                        p_threats -> setWidthHeight(100,100);
                        p_threats -> setXYThreats(rand()%600, -i*200);
                        Bullet * p_bulletThreats = new Bullet;
                        p_threats -> initBullet(p_bulletThreats);//bandan cho threats
                    }
                }
                //Play music background
                Mix_PlayMusic(g_Sound_Background,-1);
                //While application is running
                while( !quit )
                {
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    // background
                    if(ScrollBG <= 1080-SCREEN_HEIGHT) ScrollBG = 3240*2/3-SCREEN_HEIGHT;
                    ScrollBG -= STEPBG;
                    SDL_Rect gBGClip = {700, ScrollBG, SCREEN_WIDTH, SCREEN_HEIGHT};
                    gBackground.setWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT);
                    gBackground.render( 0, 0, &gBGClip);

                    //Player
                    gAircraft.setWidthHeight(WIDTH_AIRCRAFT, HEIGHT_AIRCRAFT);
                    gAircraft.render( x, y);

                    //text
                    std::string TextScore =  "Score: " + std::to_string(SCORE) +"        Chance: " + std::to_string(PLAYERPOWER-Player_Die) ;
                    gText.loadFromRenderedText(TextScore.c_str(), textColor);
                    gText.render(10,10);

                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT ){
                            quit = true;
                        }
                        if (e.type == SDL_KEYDOWN) {
                            if (e.key.keysym.sym == SDLK_ESCAPE) quit = true;

                            if (e.key.keysym.sym == SDLK_LEFT){
                                    x=(x-step+SCREEN_WIDTH-gAircraft.getWidth())%(SCREEN_WIDTH-gAircraft.getWidth());
                                }
                            if (e.key.keysym.sym == SDLK_RIGHT){
                                    x=(x+step)%(SCREEN_WIDTH-gAircraft.getWidth());
                                }
                            if (e.key.keysym.sym == SDLK_DOWN){
                                    if( y <= SCREEN_HEIGHT- gAircraft.getHeight())
                                        y=y+step;
                                }
                            if (e.key.keysym.sym == SDLK_UP){
                                    if(y >= 0 )
                                        y=y-step;
                                }
                            if(e.key.keysym.sym == SDLK_BACKSPACE){

                            }
                        }

                        if(e.type == SDL_MOUSEBUTTONDOWN){
                            Bullet* p_bullet = new Bullet();
                            p_bullet -> setLocation(x, y);
                            if(e.button.button == SDL_BUTTON_LEFT){
                                Mix_PlayChannel(-1, g_Sound_Bullet, 0);
                                p_bullet -> setWidthHeight(WIDTH_SPHERE, HEIGHT_SPHERE);
                                p_bullet ->loadFromFile("sphere.png");
                                p_bullet ->set_is_move(true);
                                p_bullet_list_.push_back(p_bullet);

                            }
                            else if(e.button.button == SDL_BUTTON_RIGHT){
                                Mix_PlayChannel(-1, g_Sound_Laser, 0);
                                p_bullet -> setWidthHeight(WIDTH_LASER, HEIGHT_LASER);
                                p_bullet ->loadFromFile("laser.png");
                                p_bullet ->set_is_move(true);
                                p_bullet_list_.push_back(p_bullet);
                            }

                        }//mouse
                    }//event
                    //hien thi băn dạn cho nhan vat
                    for(int i = 0; i< p_bullet_list_.size(); i++)
                    {
                        Bullet* p_bullet = p_bullet_list_.at(i);
                        if(p_bullet != NULL)
                        {
                            if(p_bullet -> get_is_move() == true)
                            {
                                p_bullet -> HandleMove();
                                p_bullet -> render(p_bullet -> getXLocation()+WIDTH_AIRCRAFT/2 ,p_bullet ->getYLocation()-15);
                            }
                            else
                            {
                                p_bullet_list_.erase(p_bullet_list_.begin()+i);
                                if(p_bullet != NULL)
                                {
                                    delete p_bullet;
                                    p_bullet = NULL;
                                }
                            }
                        }
                    }//for
                    //Run Threats
                    for(int i = 0; i < NUMTHREATS; i++)
                    {
                        Threats * p_threats = (p_threat +i);
                        if(p_threats)
                        {
                            p_threats -> HandleMove();
                            p_threats -> render(p_threats -> getXThreats(), p_threats -> getYThreats());
                            p_threats ->makeBullet();

                            //check Collision player and threats
                            bool is_col = CheckCollision(0,x-5,y,p_threats -> getXThreats()-5, p_threats -> getYThreats());
                            if(is_col)
                            {
                                //Play Sound Broken
                                 Mix_PlayChannel(-1,g_Sound_Broken,0);
                                for(int frameboom = 0 ; frameboom < 8*FRAME; frameboom++)
                                {
                                    gBoom.render((x+ p_threats -> getXThreats())/2,(y+ p_threats -> getYThreats())/2,&gBoomClip[frameboom/FRAME]);
                                    SDL_RenderPresent(gRenderer);
                                }
                                Player_Die++;
                                if(Player_Die<PLAYERPOWER)
                                {
                                    SDL_Delay(1000);
                                    x= SCREEN_WIDTH/2-50;
                                    y = SCREEN_HEIGHT-100;
                                }
                                else
                                {
                                    quit = true;
                                }





                            }

                            //checkcollision bulletplayer and threats
                            for(int bl = 0; bl < p_bullet_list_.size(); bl++)
                            {
                                Bullet * p_bullet = p_bullet_list_.at(bl);
                                bool bul_col = CheckCollision(1,p_bullet ->getXLocation()+WIDTH_AIRCRAFT/2, p_bullet -> getYLocation(),p_threats -> getXThreats()+5, p_threats -> getYThreats() );
                                if(bul_col)
                                {
                                    SCORE++;
                                    p_threats -> setXYThreats(rand()%(SCREEN_WIDTH-WIDTH_AIRCRAFT), -HEIGHT_AIRCRAFT);
                                    // level up
                                    if(SCORE%10 == 0)
                                    {
                                        STEPBG ++;
                                        STEPBULLET ++;
                                    }

                                }
                            }// FOR CHECKCOLLISION

                            std::vector<Bullet*> bullet_list_threats = p_threats -> GetBulletThreatsList();
                            for(int bl = 0; bl < bullet_list_threats.size(); bl++)
                            {
                                Bullet * p_bullet_threats = bullet_list_threats.at(bl);
                                //bullet threats vs Player
                                bool bul_col = CheckCollision(-1,p_bullet_threats ->getXLocation()+WIDTH_AIRCRAFT/2, p_bullet_threats -> getYLocation(),x+5, y );
                                if(bul_col)
                                {
                                    Mix_PlayChannel(-1,g_Sound_Broken,0);
                                    for(int frameboom = 0 ; frameboom < 8*FRAME; frameboom++)
                                    {
                                        gBoom.render(x,y,&gBoomClip[frameboom/FRAME]);
                                        SDL_RenderPresent(gRenderer);
                                    }
                                    Player_Die++;
                                    if(Player_Die<PLAYERPOWER)
                                    {
                                        SDL_Delay(500);
                                        x= SCREEN_WIDTH/2-50;
                                        y = SCREEN_HEIGHT-100;
                                    }
                                    else
                                    {
                                        quit = true;
                                    }


                                }//bul_col
                            }//for bul_col
                        }// a threats

                    }// for threats

                    //Update screen
                    SDL_RenderPresent( gRenderer );


                }// while quit
                gMenu.loadOutroGame(e);
                if(gMenu.getis_Play())
                {
                    STEPBG -= SCORE/10;
                    STEPBULLET -= SCORE/10;
                    Player_Die = 0;
                    SCORE = 0;
                }
            }//while menu play



		}// load media success
	}// init success
	//Free resources and close SDL
	close();
	return 0;
}
