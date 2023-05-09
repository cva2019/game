

#include "Bullet.h"
Bullet::Bullet()
{
  x_val_ = 0;
  y_val_ = 0;
  is_move_=false;

}

Bullet::~Bullet()
{

}

Bullet* Bullet::Clone()
{
    Bullet* p_object_clone = new Bullet();
    p_object_clone->bullet_dir_ = this->bullet_dir_;
    p_object_clone->is_move_ = this->is_move_;
    p_object_clone->x_val_ = this->x_val_;
    p_object_clone->y_val_ = this->y_val_;

    return p_object_clone;
}
void Bullet::HandelMove(const int& x_border, const int& y_border, bool is_player)
{
     
  if (bullet_dir_ == DIR_RIGHT)
  {
          rect_.x += x_val_;
          if (rect_.x > x_border) 
          {
              is_move_ = false;
          }
  }
  else if (bullet_dir_ == DIR_LEFT)
  {
          rect_.x -= x_val_;
          if (rect_.x < 0) 
          {
              is_move_ = false;
          }
      }
  }
