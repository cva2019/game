

#include "Player.h"
#include <SDL_mixer.h>
#define USE_AUDIO
#define  NUM_FRAME 7

Player::Player()
{
  frame_ = 0;
  x_pos_ = 0;
  y_pos_ = 0;
  x_val_ = 0;
  y_val_ = 0;
  think_time_ = 0;
  width_frame_ = 0;
  height_frame_ = 0;
  status_ = -1;
  map_x_ = 0;
  map_y_ = 0;
  on_ground_ = false;
  input_type_.left_ = 0;
  input_type_.right_ = 0;
  input_type_.down_ = 0;
  input_type_.jump_ = 0;
  input_type_.up_ = 0;
  money_count_ = 0;
  power=0;
  status_ = WALK_NONE;
  is_jump_=false;
  is_bullet_=false;

}




Player::~Player()
{
  Free();
}


SDL_Rect Player::GetRectFrame()
{
  SDL_Rect rect;
  rect.x = rect_.x;
  rect.y = rect_.y;
  rect.w = rect_.w/NUM_FRAME;
  rect.h = rect_.h;
  return rect;
}

void Player::HandleInputAction(SDL_Event events, SDL_Renderer* screen,Mix_Chunk* gsound1)
{

  if( events.type == SDL_KEYDOWN )
  {
    switch( events.key.keysym.sym )
    {
    case SDLK_RIGHT:
      {
        status_  = WALK_RIGHT;
        input_type_.right_ = 1;
        UpdateImagePlayer(screen);
        break;
      }
    case SDLK_LEFT:
      {
        status_ = WALK_LEFT;
        input_type_.left_ = 1;
        UpdateImagePlayer(screen);
        break;
      }
      case SDLK_UP:
      {
        is_jump_=true;
        input_type_.jump_=1;
        UpdateImagePlayer(screen);
        break;
      }
      case SDLK_DOWN:
      {
         is_bullet_=true;
         input_type_.down_=1;
         Bullet* p_bullet = new Bullet();
         p_bullet->LoadImg("img//player_bullet.png", screen);


#ifdef USE_AUDIO
       Mix_PlayChannel(-1, gsound1, 0 );
#endif
      if (status_ == WALK_LEFT)
      {
        p_bullet->set_dir_bullet(Bullet::DIR_LEFT);
        p_bullet->SetRect(this->rect_.x, this->rect_.y + height_frame_*0.36);
      }
      else
      {
        p_bullet->set_dir_bullet(Bullet::DIR_RIGHT);
        p_bullet->SetRect(this->rect_.x + width_frame_ - 20, this->rect_.y + height_frame_*0.36);
      }

      p_bullet->set_x_val(20);
      p_bullet->set_y_val(20);
      p_bullet->set_is_move(true);
      p_bullet_list_.push_back(p_bullet);
      UpdateImagePlayer(screen);
      break;
     }

      }
    }

   else if( events.type == SDL_KEYUP )
  {

      switch( events.key.keysym.sym )
      {
      case SDLK_RIGHT: input_type_.right_ = 0; break;
      case SDLK_LEFT: input_type_.left_ = 0; break;
      case SDLK_UP: input_type_.jump_=0;break;
      case SDLK_DOWN: input_type_.down_=0; break;

          break;
      }
  }
}

void Player::HandleBullet(SDL_Renderer* des)
{
  for (int i = 0; i < p_bullet_list_.size(); i++)
  {
    Bullet* p_bullet = p_bullet_list_.at(i);
    if (p_bullet != NULL)
    {
      if (p_bullet->get_is_move())
      {
        p_bullet->HandelMove(SCREEN_WIDTH, SCREEN_HEIGHT);
        p_bullet->Render(des);
      }
      else
      {
        if (p_bullet != NULL)
        {
          p_bullet_list_.erase(p_bullet_list_.begin() + i);
          delete p_bullet;
          p_bullet = NULL;
        }
      }
    }
  }
}

void Player::RemoveBullet(const int& idx)
{
  if (p_bullet_list_.size() > 0 && idx < p_bullet_list_.size())
  {
    Bullet* p_bullet = p_bullet_list_.at(idx);
    p_bullet_list_.erase(p_bullet_list_.begin() + idx);

    if (p_bullet)
    {
      delete p_bullet;
      p_bullet = NULL;
    }
  }
}

bool Player::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    width_frame_ = rect_.w/NUM_FRAME;
    height_frame_ = rect_.h;
  }

  return ret;
}

void Player::set_clips()
{
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

void Player::Show(SDL_Renderer* des)
{

  UpdateImagePlayer(des);

  if((input_type_.left_ == 1 ||
    input_type_.right_ == 1  ))
  {
    frame_++;
  }
  else
  {
    frame_ = 0;
  }

  if( frame_ >= 7 )
  {
    frame_ = 0;
  }

  if (think_time_ == 0)
  {
    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_- map_y_;

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

void Player::MovePlayer(Map& g_map)
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
      if (on_ground_ == true)
      {
        y_val_ = -PLAYER_HIGHT_VAL;
      }
      on_ground_ = false;
      input_type_.jump_ = 0;
    }

    CheckToMap(g_map);

    CenterEntityOnMap(g_map);
  }

  if (think_time_ > 0)
  {
      think_time_--;

      if (think_time_ == 0)
      {
          if (x_pos_ > 25600)
          {
              x_pos_ -= 224;
          }
          else
          {
          x_pos_ = 0;
          y_pos_ = 0;
          x_val_ = 0;
          y_val_ = 0;
          on_ground_ = false;
          }
      }
  }
}

void Player::CenterEntityOnMap(Map& g_map)
{
  g_map.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);

  if (g_map.start_x_ < 0)
  {
    g_map.start_x_ = 0;
  }

  else if (g_map.start_x_ + SCREEN_WIDTH >= g_map.max_x_)
  {
    g_map.start_x_= g_map.max_x_ - SCREEN_WIDTH;
  }

  g_map.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);

  if (g_map.start_y_ < 0)
  {
    g_map.start_y_ = 0;
  }

  else if (g_map.start_y_+ SCREEN_HEIGHT >= g_map.max_y_)
  {
    g_map.start_y_ = g_map.max_y_ - SCREEN_HEIGHT;
  }
}

void Player::CheckToMap(Map& g_map)
{
  int x1 = 0;
  int x2 = 0;
  int y1 = 0;
  int y2 = 0;
  int height_min =    height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

  x1 = (x_pos_ + x_val_) / TILE_SIZE;
  x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

  y1 = (y_pos_) / TILE_SIZE;
  y2 = (y_pos_ + height_min - 1) / TILE_SIZE;
  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
      if (x_val_ > 0)
      {
          int val1 = g_map.tile[y1][x2];
          int val2 = g_map.tile[y2][x2];

          if (val1 == STATE_MONEY || val2 == STATE_MONEY)
          {
              g_map.tile[y1][x2] = 0;
              g_map.tile[y2][x2] = 0;
              IncreaseMoney();

          }
          else if(val1== POWER || val2==POWER)
          {
            g_map.tile[y1][x2] = 0;
            g_map.tile[y2][x2] = 0;
           IncreasePower();
          }
          else
          {
              if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
              {
                  x_pos_ = x2 * TILE_SIZE;
                  x_pos_ -= width_frame_ + 1;
                  x_val_ = 0;
              }
          }
    }
    else if (x_val_ < 0)
    {
        int val1 = g_map.tile[y1][x1];
        int val2 = g_map.tile[y2][x1];
        if (val1 == STATE_MONEY || val2 == STATE_MONEY )
        {
            g_map.tile[y1][x1] = 0;
            g_map.tile[y2][x1] = 0;
            IncreaseMoney();

        }
        else if(val1==POWER || val2==POWER)
        {
          g_map.tile[y1][x1] = 0;
          g_map.tile[y2][x1] = 0;
          IncreasePower();
        }

        else
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y2][x1] != BLANK_TILE))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }
  }
  int width_min =  width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
  x1 = (x_pos_) / TILE_SIZE;
  x2 = (x_pos_ + width_min) / TILE_SIZE;

  y1 = (y_pos_ + y_val_) / TILE_SIZE;
  y2 = (y_pos_ + y_val_ + height_frame_ -1) / TILE_SIZE;

  if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
  {
      if (y_val_ > 0)
      {
          int val1 = g_map.tile[y2][x1];
          int val2 = g_map.tile[y2][x2];

          if (val1 == STATE_MONEY || val2 == STATE_MONEY )
          {
              g_map.tile[y2][x1] = 0;
              g_map.tile[y2][x2] = 0;
              IncreaseMoney();
          }
          else if(val1==POWER || val2==POWER)
          {
             g_map.tile[y2][x1] = 0;
             g_map.tile[y2][x2] = 0;
             IncreasePower();
          }
          else
          {
              if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
              {
                  y_pos_ = y2 * TILE_SIZE;
                  y_pos_ -= height_frame_;

                  y_val_ = 0;

                  on_ground_ = true;
                  if (status_ == WALK_NONE)
                  {
                      status_ = WALK_RIGHT;
                  }
              }
          }

      }
      else if (y_val_ < 0)
      {
          int val1 = g_map.tile[y1][x1];
          int val2 = g_map.tile[y1][x2];

          if (val1 == STATE_MONEY || val2 == STATE_MONEY )
          {
              g_map.tile[y1][x2] = 0;
              g_map.tile[y1][x2] = 0;
              IncreaseMoney();


          }
          else if(val1==POWER || val2==POWER)
          {
            g_map.tile[y1][x2] = 0;
            g_map.tile[y1][x2] = 0;
            IncreasePower();
          }

          else
          {
              if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
              {
                  y_pos_ = (y1 + 1) * TILE_SIZE;

                  y_val_ = 0;
              }
          }
      }
  }
  x_pos_ += x_val_;//(no collision)
  y_pos_ += y_val_;

  if (x_pos_ < 0)
  {
    x_pos_ = 0;

  }
  else if (x_pos_ + width_frame_ >= g_map.max_x_)
  {
    x_pos_ = g_map.max_x_ - width_frame_ - 1;
    Is_win=true;

  }

 if (y_pos_ > g_map.max_y_)
  {

    think_time_=40;
  }

}


void Player::IncreaseMoney()
{
 money_count_++;

}
void Player::IncreasePower()
{
  power++;

}

void Player::UpdateImagePlayer(SDL_Renderer* des)
{
    if (on_ground_ == true)
    {
        if (status_ == WALK_LEFT )
        {
            if (input_type_.up_ == 0)
            {
                LoadImg(g_name_main_left, des);
            }
        }
        else
        {
            if (input_type_.up_ == 0)
            {
                LoadImg(g_name_main_right, des);
            }

        }
    }
    else
    {
        if (status_ == WALK_LEFT)
        {
            if (input_type_.left_ == 1)
            {
                if (input_type_.up_ == 0)
                {
                    LoadImg("img//jum_left.png", des);

                }

            else
            {
                if (input_type_.up_ == 0)
                {
                    LoadImg("img//jum_left.png", des);
                }

            }
        }
        else
        {
            if (input_type_.right_ == 1)
            {
                if (input_type_.up_ == 0)
                {
                   LoadImg("img//jum_right.png", des);

                }
            }
            else
            {
                if (input_type_.up_ == 0)
                {
                    LoadImg("img//jum_right.png", des);
                }

            }
     }
    }
    set_clips();
}
}
