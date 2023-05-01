
#ifndef BASIC_OBJECT_H_
#define BASIC_OBJECT_H_

#include "CommonFunction.h"

class BaseObject
{
public:
  BaseObject();
  ~BaseObject();
  virtual bool LoadImg(std::string path, SDL_Renderer* screen);
  void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
  
  void Free();
  void SetRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;};
  SDL_Rect GetRect() const {return rect_;}
  SDL_Texture* GetObject() {return pobject;}

  void setColor(const Uint8& red, const Uint8& green, const Uint8& blue);
  void setAlpha(const Uint8& alpha);
  void setBlendMode(const SDL_BlendMode& blending);

protected:
  SDL_Texture* pobject; 
  SDL_Rect rect_;
};


#endif