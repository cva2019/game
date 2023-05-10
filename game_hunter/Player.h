
#ifndef PLAYER_H_
#define PLAYER_H_

#include "CommonFunction.h"
#include "BaseObject.h"
#include "Bullet.h"
#include <SDL_mixer.h>

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define PLAYER_SPEED 8
#define PLAYER_HIGHT_VAL 18;


class Player : public BaseObject
{
public:
  Player();
  ~Player();

  enum WalkType
  {
    WALK_NONE = 0,
    WALK_RIGHT = 1,
    WALK_LEFT = 2,
  };

  void set_clips();
  bool LoadImg(std::string path, SDL_Renderer* screen);
  void Show(SDL_Renderer* des);
  void HandleInputAction(SDL_Event events, SDL_Renderer* screen,Mix_Chunk* gsound1); 
  void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x, map_y_ = map_y;};

  void MovePlayer(Map& g_map);

  void CenterEntityOnMap(Map& g_map);
  void CheckToMap(Map& g_map);
  

  std::vector<Bullet*> get_bullet_list() const {return p_bullet_list_;}
  void set_bullet_list(std::vector<Bullet*> bullet_list)
  {
    p_bullet_list_ = bullet_list;
  }

  void HandleBullet(SDL_Renderer* des);
  void RemoveBullet(const int& idx);

  int get_frame_width() const {return width_frame_;}
  int get_frame_height() const {return height_frame_;}
  void set_think_time(const int& think_time) {think_time_ = think_time;}
  SDL_Rect GetRectFrame();
  void UpdateImagePlayer(SDL_Renderer* des);
  void IncreaseMoney();
  int GetMoneyCount() const { return money_count_; };
  void IncreasePower();
  int GetPower() const { return power; };
  bool GetIsWin() const {return Is_win ;};
 
  
  
 
private:

  int money_count_;
  int power;
  std::vector<Bullet*> p_bullet_list_;

  bool is_jump_;
  bool is_bullet_;
  int frame_;
  int status_;

  SDL_Rect frame_clip_[7];
  Input input_type_;

  bool on_ground_;
  int think_time_;
  int map_x_;
  int map_y_;

  float x_val_;
  float y_val_;
  float x_pos_;
  float y_pos_;

  int width_frame_;
  int height_frame_;
  bool Is_win;
  bool Is_money;
};


#endif