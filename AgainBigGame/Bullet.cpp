#include "Bullet.h"

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


