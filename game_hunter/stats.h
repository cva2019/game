
#ifndef STATS_H_
#define  STATS_H_
#include "CommonFunction.h"
#include "BaseObject.h"
class power : public BaseObject
{
public:
  power(void);
  ~power(void);

  void SetNum(const int& num) {number_ = num;}
  void AddPos(const int& xPos);
  void Show(SDL_Renderer* screen);
  void Init(SDL_Renderer* screen);
  void InCrease();
  void Decrease();
private:
  int number_;
  std::vector<int> position_list_;
};



class money : public BaseObject
{
public:
   money(void);
    ~money(void);

    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_pos_ = x; y_pos_ = y;};
private:
    int x_pos_;
    int y_pos_;
};
#endif
