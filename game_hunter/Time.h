
#ifndef TIME_H_
#define TIME_H_

class Time
{
public:
  Time();
  void start();
  void stop();
  void pause();
  void unpause();
  int get_ticks();
  bool is_started();
  bool is_paused();

private:
  int start_tick_;
  int paused_ticks_;
  bool is_paused_;
  bool is_started_;
};

#endif