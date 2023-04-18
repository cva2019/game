

#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"

class BulletObject : public BaseObject
{
public:
  BulletObject();
  ~BulletObject();


  enum BulletDir
  {
    DIR_RIGHT = 20,
    DIR_LEFT = 21,
  };

  void HandleInputAction(SDL_Event events);
  void HandelMove(const int& x_border, const int& y_border, bool is_player = true);
  void set_x_val(const int& x_val) {x_val_ = x_val;}
  void set_y_val(const int& y_val) {y_val_ = y_val;}

  int get_x_val() const {return x_val_;}
  int get_y_val() const {return y_val_;}
  void set_is_move(const bool& is_move) {is_move_ = is_move;} 
  bool get_is_move()const {return is_move_;}
  void set_dir_bullet(const int& dir_type) {bullet_dir_ = dir_type;}
  BulletObject* Clone();
private:
  int x_val_;
  int y_val_;
  bool is_move_;
  int bullet_dir_;

};

#endif