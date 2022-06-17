#include "Scope.h"
#include "Screen.h"
#include <SparkFun_MMA8452Q.h>
#include <Wire.h>

MMA8452Q accel;

Scope::Scope(){
  Wire.begin();
  accel.begin();
}
Scope::~Scope(){
}
int Scope::get_x(){
  return scope_x;
}
int Scope::get_y(){
  return scope_y;
}
void Scope::set_scope(){
  if(scope_visible == 0){
    int x_in = scope_x - 10;
    int y_in = scope_y - 9;
    for(int i = 0; i <= (2*10); i++){
      disp->invert_pixel(x_in+i,scope_y);
    }
    for(int i = 0; i <= (2*9); i++){
      disp->invert_pixel(scope_x,y_in+i);
    }
    for(int i = 0; i <= 4; i++){
      disp->invert_pixel((scope_x-2)+i,scope_y);
    }
    for(int i = 0; i <= 4; i++){
      disp->invert_pixel(scope_x,(scope_y-2)+i);
    }
    disp->invert_pixel(scope_x,scope_y);
    scope_visible = 1;
  }
}
void Scope::move_scope(int x, int y){
  remove_scope();
  x = scope_x + x;
  y = scope_y + y;
  set_scope_coord(x,y);
  set_scope();
}
void Scope::remove_scope(){
  if(scope_visible == 1){
    int x_in = scope_x - 10;
    int y_in = scope_y - 9;
    for(int i = 0; i <= (2*10); i++){
      disp->invert_pixel(x_in+i,scope_y);
    }
    for(int i = 0; i <= (2*9); i++){
      disp->invert_pixel(scope_x,y_in+i);
    }
    for(int i = 0; i <= 4; i++){
      disp->invert_pixel((scope_x-2)+i,scope_y);
    }
    for(int i = 0; i <= 4; i++){
      disp->invert_pixel(scope_x,(scope_y-2)+i);
    }
    disp->invert_pixel(scope_x,scope_y);
    scope_visible = 0;
  }
}
void Scope::update_scope(){
  double z = 0;
  double y = 0;
  if (accel.available()) {
    z = accel.getCalculatedZ();
    y = accel.getCalculatedY();
  }
  disp->led_off();
  calc_move_scope(z,y);
}
void Scope::calc_move_scope(double z, double y){
  int y_move = 0;
  int x_move = 0;
  if(z > .8){
    y_move = 2;
  }
  else if(z > .6){
    y_move = 1;
  }
  else if(z < -.1){
    y_move = -2;
  }
  else if(z < .1){
    y_move = -1;
  }

  x_move = calc_x_move(y,y_move);
  
  move_scope(x_move,y_move);
}
int Scope::calc_x_move(double y, int y_move){
  int x_move = 0;
  if(y_move == -2){
    if(y > .42){
      x_move = 2;
    }
    else if(y > .2){
      x_move = 1;
    }
    else if(y < -.42){
      x_move = -2;
    }
    else if(y < -.2){
      x_move = -1;
    }
  }
  if(y_move == -1){
    if(y > .45){
      x_move = 2;
    }
    else if(y > .2){
      x_move = 1;
    }
    else if(y < -.45){
      x_move = -2;
    }
    else if(y < -.2){
      x_move = -1;
    }
  }
  if(y_move == 0){
    if(y > .4){
      x_move = 2;
    }
    else if(y > .2){
      x_move = 1;
    }
    else if(y < -.4){
      x_move = -2;
    }
    else if(y < -.2){
      x_move = -1;
    }
  }
  if(y_move == 1){
    if(y > .34){
      x_move = 2;
    }
    else if(y > .17){
      x_move = 1;
    }
    else if(y < -.34){
      x_move = -2;
    }
    else if(y < -.17){
      x_move = -1;
    }
  }
  if(y_move == 2){
    if(y > .3){
      x_move = 2;
    }
    else if(y > .15){
      x_move = 1;
    }
    else if(y < -.3){
      x_move = -2;
    }
    else if(y < -.15){
      x_move = -1;
    }
  }

  return x_move;
}
void Scope::set_scope_coord(int x, int y){
  if(scope_visible == 0){
    if(x<0){
      scope_x = 0;
    }
    else if(x>83){
      scope_x = 83;
    }
    else{
      scope_x = x;
    }
    if(y<0){
      scope_y = 0;
    }
    else if(y>47){
      scope_y = 47;
    }
    else{
      scope_y = y;
    }
  }
}
