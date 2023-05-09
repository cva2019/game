

#include "stats.h"


power::power(void)
{

}


power::~power(void)
{

}


void power::AddPos(const int& xPos)
{
  position_list_.push_back(xPos);
}

void power::Show(SDL_Renderer* screen)
{
  for (int i = 0; i < position_list_.size(); i++)
  {
    rect_.x = position_list_.at(i);
    rect_.y = 0;
    Render(screen);
  }
}

void power::Init(SDL_Renderer* screen)
{
  LoadImg("img//power.png", screen);
  number_ = 4;
  if (position_list_.size() > 0)
  {
    position_list_.clear();
  }

  AddPos(20);
  AddPos(70);
  AddPos(120);
  AddPos(170);
}

void power::Decrease()
{
  number_--;
  position_list_.pop_back();
}


//Player Money

money::money()
{

}

money::~money()
{

}


void money::Init(SDL_Renderer* screen)
{
    LoadImg("img//money.png", screen);
}


void money::Show(SDL_Renderer* screen)
{
   rect_.x = x_pos_;
   rect_.y = y_pos_;
   Render(screen);
}
money1:: money1()
{

}
money1::~money1()
{

}
void money1::Init(SDL_Renderer* screen)
{
    LoadImg("img//money1.png", screen);
}


void money1::Show(SDL_Renderer* screen)
{
   rect_.x = x_pos_;
   rect_.y = y_pos_;
   Render(screen);
}