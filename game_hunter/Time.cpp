

#include "Time.h"
#include "CommonFunction.h"

Time::Time()
{
  start_tick_ = 0;
  paused_ticks_ = 0;
  is_paused_ = false;
  is_started_ = false;
}

void Time::start()
{
  is_started_ = true;
  is_paused_ = false;
  start_tick_ = SDL_GetTicks();
}

void Time::stop()
{
  is_started_ = false;
  is_paused_ = false;
}

void Time::pause()
{
  if( ( is_started_ == true ) && ( is_paused_ == false ) )
  {
    is_paused_ = true;
    paused_ticks_ = SDL_GetTicks() - start_tick_;
  }
}

void Time::unpause()
{
  if( is_paused_ == true )
  {
    is_paused_ = false;
   
    start_tick_ = SDL_GetTicks() - paused_ticks_;
   
    paused_ticks_ = 0;
  }
}

int Time::get_ticks()
{
  if( is_started_ == true )
  {
    
    if( is_paused_ == true )
    {
      return paused_ticks_;
    }
    else
    {
      return SDL_GetTicks() - start_tick_;
    }
  }

 
  return 0;
}

bool Time::is_started()
{
  return is_started_;
}

bool Time::is_paused()
{
  return is_paused_;
}