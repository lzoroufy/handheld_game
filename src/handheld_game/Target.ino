/*
 * This class generates targets for the player to shoot.
 */
#include "Target.h"
#include "Screen.h"
#include "Target_list.h"

Target::Target(){
  pinMode(17,INPUT);
  randomSeed(analogRead(17));
  create_target();
}
Target::~Target(){
}
//Creates a target of a random location and size
void Target::create_target(){
  int s = random(0,3);
  int x = 0;
  int y = 0;
  if(s == 0){
    x = random(5,79);
    y = random(5,43);
  }
  if(s == 1){
    x = random(6,78);
    y = random(6,42);
  }
  if(s == 2){
    x = random(7,77);
    y = random(7,41);
  }
  set_target(x,y,s);
}
//set_target sets the size and point value of the targets
void Target::set_target(int x, int y, int s){
  int r = 0;
  int p = 0;
  if(s == 0){
    r = 5;
    p = 200;
  }
  else if(s == 1){
    r = 6;
    p = 100;
  }
  else if(s == 2){
    r = 7;
    p = 50;
  }
  add_target(x,y,r);
}
//add_target displays the target to the screen if it is not overlapping with another target 
void Target::add_target(int x, int y, int r){
  int avail = 1;
  for(int i = 0; i < r; i++){
    for(int j = 0; j < (r-i); j++){
      if(tl->is_available(x+i,y+j) != 1){
        avail = 0;
      }
      if(tl->is_available(x-i,y+j) != 1){
        avail = 0;
      }
      if(tl->is_available(x+i,y-j) != 1){
        avail = 0;
      }
      if(tl->is_available(x-i,y-j) != 1){
        avail = 0;
      }
    }
  }
  if(avail == 1){
    for(int i = 0; i < r; i++){
      for(int j = 0; j < (r-i); j++){
        tl->update_list(x+i,y+j);
        tl->update_list(x-i,y+j);
        tl->update_list(x+i,y-j);
        tl->update_list(x-i,y-j);
        if(j != (r - i - 2)){
          disp->set_pixel(x+i,y+j);
          disp->set_pixel(x-i,y+j);
          disp->set_pixel(x+i,y-j);
          disp->set_pixel(x-i,y-j);
        }
      }
    }
    disp->remove_pixel(x,y);
    tl->target_added();
  }
}
