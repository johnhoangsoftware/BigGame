#ifndef THREATS_H
#define THREATS_H

#include "Bullet.h"
#include "Variable.h"

using namespace std;

#define WIDTH_THREATS ;
#define HEIGHT_THREATS;

class Threats : public LTexture
{
public:
    Threats();
    ~Threats();
    void HandleMove();
    int setXYThreats(const int &x, const int& y){x_threats = x; y_threats = y;};
    int getXThreats(){return x_threats;};
    int getYThreats(){return y_threats;};
    void initBullet(Bullet* p_bullet);// taoj doois tuongwj
    void makeBullet();//Ban dan
    std::vector<Bullet*> GetBulletThreatsList() const {return p_bullet_list;};

private:
    int widthFrame ;
    int heightFrame;
    int x_threats;
    int y_threats;
    std::vector<Bullet*> p_bullet_list;
};


Threats::Threats()
{
    widthFrame = 50;
    heightFrame = 50;
    x_threats = rand()%(SCREEN_WIDTH-WIDTH_AIRCRAFT);
    y_threats = 0;
}

Threats::~Threats()
{
    if( p_bullet_list.size()>0)
    {
        for(int i = 0; i< p_bullet_list.size(); i++)
        {
            Bullet* p_bullet = p_bullet_list.at(i);
            if(p_bullet != NULL)
            {
                delete p_bullet;
                p_bullet = NULL;
            }
        }
        p_bullet_list.clear();
    }

}

void Threats::HandleMove(){



    //x_threats = (x_threats + rand_x)%SCREEN_WIDTH;
    y_threats += STEPBG+1;
    if(y_threats> SCREEN_HEIGHT) {
        y_threats = 0;
        x_threats = rand()%(SCREEN_WIDTH-100);
    }
}

void Threats::initBullet(Bullet* p_bullet){
    if(p_bullet){
        if(p_bullet -> loadFromFile("sphere1.png")){

            p_bullet -> set_is_move(true);
            p_bullet -> setWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
            p_bullet -> setLocation(x_threats,y_threats);
            p_bullet_list.push_back(p_bullet);

        }
    }
}

 void Threats::makeBullet(){
    for(int i = 0; i< p_bullet_list.size(); i++)
    {
        Bullet* p_bullet = p_bullet_list.at(i);

        if(p_bullet)
        {
            if(p_bullet -> get_is_move())
            {
                p_bullet -> HandleMoveThreats();
                p_bullet -> render(p_bullet -> getXLocation()+50 ,p_bullet ->getYLocation()+100);
            }
            else
            {
                p_bullet -> set_is_move(true);
                p_bullet -> setLocation(x_threats,y_threats);
            }
        }
    }

 }

#endif // THREATS_H


