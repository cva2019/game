

#include "Mobs.h"



Mobs::Mobs()
{
  rect_.x = SCREEN_WIDTH;
  rect_.y = 0;
  width_frame_ = 0;
  height_frame_ = 0;
  x_val_ = 0;
  y_val_ = 0;
  x_pos_ = 0;
  y_pos_ = 0;
  on_ground_ = 0;
  think_time_ = 0;
  input_type_.left_ = 1;
  frame_ = 0;
  type_move_ = MOVE_IN_SPACE_TH;
  input_type_.left_ = 0;


}


Mobs::~Mobs()
{
  if (bullet_list_.size() > 0)
  {
    for (int i = 0; i <bullet_list_.size(); i++)
    {
      Bullet* p_bullet = bullet_list_.at(i);
      if (p_bullet != NULL)
      {
        delete p_bullet;
        p_bullet = NULL;
      }
    }
    bullet_list_.clear();
  }
}

SDL_Rect Mobs::GetRectFrame()
{
  SDL_Rect rect;
  rect.x = rect_.x;
  rect.y = rect_.y;
  rect.w = rect_.w/NUM_FRAME;
  rect.h = rect_.h;

  return rect;
}

void Mobs::ResetBullet(Bullet* p_bullet)
{

    if(input_type_.right_==1)
       {
        p_bullet->set_dir_bullet(Bullet::DIR_RIGHT);
        p_bullet->SetRect(rect_.x+width_frame_ -20, rect_.y+10);
       }
    else if(input_type_.left_==1)
       {
        p_bullet->set_dir_bullet(Bullet::DIR_LEFT);
        p_bullet->SetRect(rect_.x,rect_.y+10);
       }
    p_bullet->set_x_val(10);
}

void Mobs::InitBullet(Bullet* p_bullet,  SDL_Renderer* screen,const int& bullet_type_)
{
  if (p_bullet)
  {
     bool ret=false;
     switch(bullet_type_)
     {
      case 1:
      ret = p_bullet->LoadImg("img//bullet1.png",screen);
      break;
      case 2:
      ret=p_bullet->LoadImg("img//bullet2.png",screen);
      break;
      default:
      break;

     }
      if (ret)
       {
       if(input_type_.right_==1)
       {
        p_bullet->set_dir_bullet(Bullet::DIR_RIGHT);
        p_bullet->SetRect(rect_.x+width_frame_ -20, rect_.y+10);
       }
       else if(input_type_.left_==1)
       {
        p_bullet->set_dir_bullet(Bullet::DIR_LEFT);
        p_bullet->SetRect(rect_.x,rect_.y+10);
       }
        p_bullet->set_is_move(true);
        p_bullet->set_x_val(15);
        bullet_list_.push_back(p_bullet);

       }
  }
}


void Mobs::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < bullet_list_.size(); i++)
    {
      Bullet* p_bullet = bullet_list_.at(i);
      if (p_bullet != NULL)
      {
          if (p_bullet->get_is_move())
          {
            int distance_bullet = rect_.x + width_frame_ - p_bullet->GetRect().x;
            if ( distance_bullet > 0 && distance_bullet < 400)
            {
                p_bullet->HandelMove(x_limit, y_limit);
                p_bullet->Render(des);

            }
            else
            {
               p_bullet->set_is_move(false);
            }
          }
          else
          {
            p_bullet->set_is_move(true);
         if(input_type_.left_ == 1)
       {
        p_bullet->set_dir_bullet(Bullet::DIR_LEFT);
        p_bullet->SetRect(this->rect_.x,this-> rect_.y+10);

      }
      else if(input_type_.right_==1)
      {
        p_bullet->set_dir_bullet(Bullet::DIR_RIGHT);
        p_bullet->SetRect(this->rect_.x+width_frame_ - 20,this->rect_.y+10);
      }

     }
    }
   }
 }

void Mobs::RemoveBullet(const int& idx)
{
  if (bullet_list_.size() > 0 && idx < bullet_list_.size())
  {
    Bullet* p_bullet = bullet_list_.at(idx);
    bullet_list_.erase(bullet_list_.begin() + idx);

    if (p_bullet)
    {
      delete p_bullet;
      p_bullet = NULL;
    }
  }
}

void Mobs::InitPlayer()
{
  x_val_ = 0;
  y_val_ = 0;

  if (x_pos_ > 224)
  {
      x_pos_ -= 224;
      animation_a_ -= 224;
      animation_b_ -= 224;
  }
  else
   x_pos_ = 0;
  y_pos_ = 0;
  think_time_ = 0;
  input_type_.left_ = 1;


}

bool Mobs::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    width_frame_ = rect_.w/NUM_FRAME;
    height_frame_ = rect_.h;
  }

  return ret;
}


void Mobs::set_clips()
{
  //Clip the sprites
  if (width_frame_ > 0 && height_frame_ > 0)
  {
    for(int i=0;i<NUM_FRAME;i++)
    {
      frame_clip_[i].x=width_frame_*i;
      frame_clip_[i].y=0;
      frame_clip_[i].w= width_frame_;
      frame_clip_[i].h=height_frame_;
    }
  }
}


void Mobs::SetAnimationPos(const int& pos_x_a, const int& pos_x_b)
{
  animation_b_ = pos_x_b;
  animation_a_ = pos_x_a;
}


void Mobs::ImpMoveType(SDL_Renderer* screen)
{

 if(type_move_==MOVE_IN_SPACE_TH)
  {
    if (on_ground_ == true)
    {
      if (x_pos_+40> animation_b_)
      {

        input_type_.left_ = 1;
        input_type_.right_ = 0;
        LoadImg("img//mob_left.png", screen);
      }
      else if (x_pos_ -40< animation_a_)
      {

        input_type_.right_ = 1;
        input_type_.left_ = 0;
        LoadImg("img//mob_right.png", screen);

      }
    }
    else
    {
        if (input_type_.left_ == 1)
        {
            LoadImg("img//mob_left.png", screen);

        }
    }
  }
  else if(type_move_==MOVE_1)
  {
    if (on_ground_ == true)
    {
      if (x_pos_+50> animation_b_)
      {

        input_type_.left_ = 1;
        input_type_.right_ = 0;
        LoadImg("img//mob_left1.png", screen);//
      }
      else if (x_pos_-50< animation_a_)
      {

        input_type_.right_ = 1;
        input_type_.left_ = 0;
        LoadImg("img//mob_right1.png", screen);


      }
    }
    else
    {
        if (input_type_.left_ == 1)
        {
            LoadImg("img//mob_left1.png", screen);

        }
    }
  }
  else if(type_move_==MOVE_2)
  {
    if (on_ground_ == true)
    {
      if (x_pos_+30> animation_b_)
      {

        input_type_.left_ = 1;
        input_type_.right_ = 0;
        LoadImg("img//mob_left2.png", screen);//
      }
      else if (x_pos_-40 < animation_a_)
      {

        input_type_.right_ = 1;
        input_type_.left_ = 0;
        LoadImg("img//mob_right2.png", screen);


      }
    }
    else
    {
        if (input_type_.left_ == 1)
        {
            LoadImg("img//mob_left2.png", screen);

        }
    }
  }

}

void Mobs::DoPlayer(Map& g_map)
{
  if (think_time_ == 0)
  {
    x_val_ = 0;
    y_val_ += GRAVITY_SPEED;

    if (y_val_ >= MAX_FALL_SPEED)
    {
      y_val_ = MAX_FALL_SPEED;
    }

    if (input_type_.left_ == 1)
    {
      x_val_ -= PLAYER_SPEED;
    }

    else if (input_type_.right_ == 1)
    {
      x_val_+= PLAYER_SPEED;
    }

    if (input_type_.jump_ == 1)
    {
      if (on_ground_ == 1)
      {
        y_val_ = -PLAYER_HIGHT_VAL;
      }

      input_type_.jump_ = 0;
    }

    CheckToMap(g_map);



  }

  if (think_time_ > 0)
  {
    think_time_--;

    if (think_time_ == 0)
    {
      InitPlayer();
    }
  }
}
void Mobs::CheckToMap(Map& g_map)
{
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;

  on_ground_ = 0;

  int height_min =   height_frame_ ;
  x1 = (x_pos_ + x_val_) / TILE_SIZE;
  x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

  y1 = (y_pos_) / TILE_SIZE;
  y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
    if (x_val_ > 0)
    {
      int val1 = g_map.tile[y1][x2];
      int val2= g_map.tile[y2][x2] ;

      if ((val1 != BLANK_TILE and val1 != STATE_MONEY) || (val2 != BLANK_TILE and val2 != STATE_MONEY))
      {

        x_pos_ = x2 * TILE_SIZE;
        x_pos_ -= width_frame_ + 1;
        x_val_ = 0;
    }
    else if (x_val_ < 0)
    {  int val1 = g_map.tile[y1][x1];
     int val2 = g_map.tile[y2][x1];
      if ((val1 != BLANK_TILE and val1 != STATE_MONEY) || (val2 != BLANK_TILE and val2 != STATE_MONEY))
      {
        x_pos_ = (x1 + 1) * TILE_SIZE;
        x_val_ = 0;
      }
    }
  }

  int width_min = width_frame_ ;

  x1 = (x_pos_) / TILE_SIZE;
  x2 = (x_pos_ + width_min) / TILE_SIZE;

  y1 = (y_pos_ + x_val_) / TILE_SIZE;
  y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
    if (y_val_ > 0)
    {
      int val1=g_map.tile[y2][x1];
      int val2=g_map.tile[y2][x2];
      if ((val1 != BLANK_TILE and val1 != STATE_MONEY) || (val2 != BLANK_TILE and val2 != STATE_MONEY))
      {
        y_pos_ = y2 * TILE_SIZE;
        y_pos_ -= height_frame_;

        y_val_ = 0;

        on_ground_ = 1;
    }
    else if (y_val_ < 0)
    {
      int val1=g_map.tile[y1][x1];
      int val2=g_map.tile[y1][x2];
      if ((val1 != BLANK_TILE and val1 != STATE_MONEY) || (val2 != BLANK_TILE and val2 != STATE_MONEY))
      {
        y_pos_ = (y1 + 1) * TILE_SIZE;

        y_val_ = 0;
      }
    }
  }
  x_pos_ += x_val_;
  y_pos_ += y_val_;

  if (x_pos_ < 0)
  {
    x_pos_ = 0;
  }
  else if (x_pos_ + width_frame_ >= g_map.max_x_)
  {
    x_pos_ = g_map.max_x_ - width_frame_ - 1;
  }

  if (y_pos_ > g_map.max_y_)
  {
    think_time_ = 50;
  }
}
}

void Mobs::Show(SDL_Renderer* des)
{
  if (think_time_ == 0)
  {
      rect_.x = x_pos_ - map_x_;
      rect_.y = y_pos_- map_y_;
      frame_++;
      if( frame_ >= 7 )
      {
        frame_ = 0;
      }

      SDL_Rect* currentClip = &frame_clip_[frame_];
      SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
      if (currentClip != NULL)
      {
         renderQuad.w = currentClip->w;
         renderQuad.h = currentClip->h;
      }

      SDL_RenderCopy(des, pobject, currentClip, &renderQuad );
  }
}
