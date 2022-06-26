/*
 * Timer class is a simple class that starts, stops, and resets a timer.
 */
#include "Timer.h"

Timer::Timer(long t){
  duration = t;
  current = millis();
  end_time = current + t;
}
Timer::~Timer(){
}
int Timer::is_done(){
  current = millis();
  if(current >= end_time){
    return 1;
  }
  return 0;
}
void Timer::reset(){
  current = millis();
  end_time = current + duration;
}
void Timer::reset(long t){
  duration = t;
  current = millis();
  end_time = current + t;
}
