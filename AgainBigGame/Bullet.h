
#ifndef BULLET_H
#define BULLET_H

#include "LTexture.h"
#include "Variable.h"

using namespace std;



class Bullet : public LTexture
{
public:


  Bullet();
  ~Bullet();

  void HandleInputAction(SDL_Event e);
  void HandleMove();// bắn đạn player
  void HandleMoveThreats();//băn sdanj threast
  bool get_is_move() const {return is_move_;}
  void set_is_move(bool is_move) {is_move_ = is_move;}


  void setLocation(const int& x_location_, const int& y_location_ ) {x_location = x_location_; y_location = y_location_ ;  };
  //void setYStepBullet(int set_step){y_step_bullet = set_step;};
  int getYLocation(){return y_location;};
  int getXLocation(){return x_location;};
private:
    int x_location;
    int y_location;
  int x_step_bullet;
  int y_step_bullet;
  bool is_move_;


};

Bullet::Bullet()
{
  x_step_bullet = 0;
  y_step_bullet = STEPBULLET;
  is_move_ = false;

  int x_location = 0 ;
  int y_location = 0;
}

Bullet::~Bullet()
{

}

void Bullet::HandleMove()
{
  if (is_move_ == true)
  {
    y_location -=STEPBULLET;
    if (y_location < 0)
    {
      is_move_ = false;
    }
  }
}
void Bullet::HandleMoveThreats()
{
    if (is_move_ == true)
    {

        y_location += STEPBULLET;
        if (y_location > SCREEN_HEIGHT)
        {
          is_move_ = false;
        }
    }
}








#endif
