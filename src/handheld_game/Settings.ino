/*
 * The Settings class is an optional class to manipulate the parameters of the game.
 * This class contains code to read input from a series of four switches as well as display a settings menu on the screen
 */
#include "Settings.h"
#include "Screen.h"

Settings::Settings(){
  pinMode(sw_1, INPUT);
  pinMode(sw_2, INPUT);
  pinMode(sw_3, INPUT);
  pinMode(sw_4, INPUT);
}
Settings::~Settings(){
}
void Settings::menu_loop(){
  int next = 0;
  while(next == 0){
    update_menu();
    if(digitalRead(right_button) == 1){
      next = 1;
    }
    if(digitalRead(left_button) == 1){
      next = 1;
    }
  }
}
int sw_1_prev = 0;
int sw_2_prev = 0;
int sw_3_prev = 0;
int sw_4_prev = 0;
void Settings::start_menu(){
  disp -> clear();
  disp -> update();
  for(int i = 0; i < 256; i = i + 51){
    disp->led_dim(i);
    delay(500);
  }
  disp->led_on();
  invert_box(58,77,32,41);
  invert_box(61,84,25,32);
  invert_box(73,82,16,25);
  invert_box(73,82,9,16);
  
  if(get_sw_1() == 0){
    if(sw_1_prev == 1){
    sw_1_prev = 0;
    invert_box(33,52,32,41);
    invert_box(58,77,32,41);
    }
  }
  else{
    sw_1_prev = 1;
    invert_box(33,52,32,41);
    invert_box(58,77,32,41);
  }
  if(get_sw_2() == 0){
    if(sw_2_prev == 1){
      sw_2_prev = 0;
      invert_box(42,61,24,32);
      invert_box(61,84,25,32);
    }
  }
  else{
    if(sw_2_prev == 0){
      sw_2_prev = 1;
      invert_box(42,61,24,32);
      invert_box(61,84,25,32);
    }
  }
  if(get_sw_3() == 0){
    if(sw_3_prev == 1){
      sw_3_prev = 0;
      invert_box(61,70,16,25);
      invert_box(73,82,16,25);
    }
  }
  else{
    if(sw_3_prev == 0){
      sw_3_prev = 1;
      invert_box(61,70,16,25);
      invert_box(73,82,16,25);
    }
  }
  if(get_sw_4() == 0){
    if(sw_4_prev == 1){
      sw_4_prev = 0;
      invert_box(62,71,9,16);
      invert_box(73,82,9,16);
    }
  }
  else{
    if(sw_4_prev == 0){
      sw_4_prev = 1;
      invert_box(62,71,9,16);
      invert_box(73,82,9,16);
    }
  }
  update_menu();
}
void Settings::end_menu(){
  for(int i = 255; i >= 0; i = i - 51){
    disp->led_dim(i);
    delay(500);
  }
  disp->led_off();
  disp -> clear();
  disp -> update();
}
void Settings::run_menu(){
  start_menu();
  menu_loop();
  update_values();
  end_menu();
}

void Settings::update_menu(){
  if(get_sw_1() == 0){
    if(sw_1_prev == 1){
      sw_1_prev = 0;
      invert_box(33,52,32,41);
      invert_box(58,77,32,41);
    }
  }
  else{
    if(sw_1_prev == 0){
      sw_1_prev = 1;
      invert_box(33,52,32,41);
      invert_box(58,77,32,41);
    }
  }
  if(get_sw_2() == 0){
    if(sw_2_prev == 1){
      sw_2_prev = 0;
      invert_box(42,61,24,32);
      invert_box(61,84,25,32);
    }
  }
  else{
    if(sw_2_prev == 0){
      sw_2_prev = 1;
      invert_box(42,61,24,32);
      invert_box(61,84,25,32);
    }
  }
  if(get_sw_3() == 0){
    if(sw_3_prev == 1){
      sw_3_prev = 0;
      invert_box(61,70,16,25);
      invert_box(73,82,16,25);
    }
  }
  else{
    if(sw_3_prev == 0){
      sw_3_prev = 1;
      invert_box(61,70,16,25);
      invert_box(73,82,16,25);
    }
  }
  if(get_sw_4() == 0){
    if(sw_4_prev == 1){
      sw_4_prev = 0;
      invert_box(62,71,9,16);
      invert_box(73,82,9,16);
    }
  }
  else{
    if(sw_4_prev == 0){
      sw_4_prev = 1;
      invert_box(62,71,9,16);
      invert_box(73,82,9,16);
    }
  }
  disp -> goto_XY(0,0);
  for(int i = 0; i < 504; i++){
    disp -> write(Settings_Menu[i]);
  }
}
void Settings::update_values(){
  if(get_sw_1() == 0){
    game_time = 60000;
  }
  else{
    game_time = 30000;
  }
  if(get_sw_2() == 0){
    target_gen = 500;
  }
  else{
    target_gen = 2000;
  }
  if(get_sw_3() == 0){
    total_rounds = 5;
  }
  else{
    total_rounds = 3;
  }
  if(get_sw_4() == 0){
    auto_reload = 1;
  }
  else{
    auto_reload = 0;
  }
}
int Settings::get_sw_1(){
  return digitalRead(sw_1);
}
int Settings::get_sw_2(){
  return digitalRead(sw_2);
}
int Settings::get_sw_3(){
  return digitalRead(sw_3);
}
int Settings::get_sw_4(){
  return digitalRead(sw_4);
}
long Settings::get_game_time(){
  return game_time;
}
int Settings::get_total_rounds(){
  return total_rounds;
}
long Settings::get_target_gen(){
  return target_gen;
}
int Settings::get_auto_reload(){
  return auto_reload;
}
void Settings::invert_box(int x1, int x2, int y1, int y2){
  for(int i = x1; i < x2; i++){
    for(int j = y1; j < y2; j++){
      invert_pixel(i,j);
    }
  }
}
void Settings::set_pixel(int x, int y){
  if(x>=0 && x<84 && y>=0 && y<48){
    y = 47 - y;
    byte shift = y % 8;
    Settings_Menu[x + (y/8)*84] |= 1<<shift;
  }
}
void Settings::remove_pixel(int x, int y){
  if(x>=0 && x<84 && y>=0 && y<48){
    y = 47 - y;
    byte shift = y % 8;
    Settings_Menu[x + (y/8)*84] &= ~(1<<shift);
  }
}
void Settings::invert_pixel(int x, int y){
  if(is_black(x,y)){
    remove_pixel(x,y);
  }
  else{
    set_pixel(x,y);
  }
}
boolean Settings::is_black(int x, int y){
  if(x>=0 && x<84 && y>=0 && y<48){
    y = 47 - y;
    byte shift = y % 8;
    byte target = Settings_Menu[x + (y/8)*84];
    target &= 1<<shift;
    if(target == (1<<shift)){
      return 1;
    }
  }
  return 0;
}
