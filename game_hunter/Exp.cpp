


#include "Exp.h"


Exp::Exp(void)
{

}


Exp::~Exp(void)
{

}


bool Exp::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImg(path, screen);

  if (ret == true)
  {
    frame_width_ = rect_.w/NUM_FRAME_EXP;
    frame_height_ = rect_.h;
  }

  return ret;
}

void Exp::set_clips()
{
  if (frame_width_ > 0 && frame_height_ > 0)
  {
     for(int i=0;i<NUM_FRAME_EXP;i++)
    {
      frame_clip_[i].x=frame_width_*i;
      frame_clip_[i].y=0;
      frame_clip_[i].w= frame_width_;
      frame_clip_[i].h=frame_height_;
    }
  }
}


void Exp::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, frame_width_, frame_height_};
    if (currentClip != NULL)
    {
      renderQuad.w = currentClip->w;
      renderQuad.h = currentClip->h;
    }

    SDL_RenderCopy(screen, pobject, currentClip, &renderQuad );
}
