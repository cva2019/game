

#include "BaseObject.h"



BaseObject::BaseObject()
{

  pobject=NULL;
  rect_.x = 0;
  rect_.y = 0;
  rect_.w = 0;
  rect_.h = 0;
}

BaseObject::~BaseObject()
{
  Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{

  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  if( loadedSurface != NULL )
  {

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));


    newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface );
    if(newTexture != NULL )
    {

      rect_.w = loadedSurface->w;
      rect_.h = loadedSurface->h;
    }


    SDL_FreeSurface( loadedSurface );
  }


  pobject = newTexture;
  return pobject != NULL;
}

void BaseObject::Free()
{

  if(pobject != NULL)
  {
    SDL_DestroyTexture(pobject);
    pobject = NULL;
    rect_.w = 0;
    rect_.h = 0;
  }
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /*=NULL*/)
{
  SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h};
  if (clip != NULL)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }
  SDL_RenderCopy(des, pobject, clip, &renderQuad);
}

void BaseObject::setColor(const Uint8& red, const Uint8& green, const Uint8& blue)
{
  SDL_SetTextureColorMod(pobject, red, green, blue);
}

void BaseObject::setBlendMode(const SDL_BlendMode& blending)
{
  SDL_SetTextureBlendMode(pobject, blending);
}

void BaseObject::setAlpha(const Uint8& alpha)
{
  SDL_SetTextureAlphaMod(pobject, alpha);
}
