/*
 * Game class contains the code for the main game play.
 * This class manages code for generating targets and displaying the scope.
 * The code for the interrupt buttons are here.
 */
#include "Game.h"
#include "Ammo.h"
#include "Timer.h"
#include "Screen.h"
#include "Scope.h"
#include "Target.h"
#include "Target_list.h"
#include <SparkFun_MMA8452Q.h>

Ammo *ammo;
Scope *scope;
Target_list *tl;
Game::Game(long g, long t, int r, int a){
  game_time = g;
  total_rounds = r;
  target_gen = t;
  auto_reload = a;
  ammo = new Ammo(r);
  scope = new Scope();
  long total_targets = g/t;
  total_targets = total_targets + 1;
  tl = new Target_list((int)total_targets);
}
Game::~Game(){
  delete(ammo);
  delete(scope);
  delete(tl);
}
int Game::run_game(){
  start_up();
  game_loop();
  end_game();
  return tl->get_score();
}
void Game::start_up(){
  int r = 0;
  for(int i = 0; i < 256; i = i + 51){
    disp->led_dim(i);
    set_lights(r);
    r++;
    delay(500);
  }
  set_lights(total_rounds);
  disp->led_on();
  scope->set_scope();
  disp->update();
}
void Game::end_game(){
  int l = 0;
  for(int i = 255; i >= 0; i = i - 51){
    disp->led_dim(i);
    delay(500);
    if(l == 0){
      set_lights(5);
      l = 1;
    }
    else{
      set_lights(0);
      l = 0;
    }
  }
  scope->remove_scope();
  disp->clear();
  disp->update();
  disp->led_off();
  set_lights(0);
}
//game_loop manages the time in the round and the time to generate new targets.
void Game::game_loop(){
  long rc = 500;
  Timer *game_clock = new Timer(game_time);
  Timer *scope_clock = new Timer(100);
  Timer *target_clock = new Timer(target_gen);
  Timer *reload_clock = new Timer(rc);
  set_target();
  reloading = 0;
  while(game_clock->is_done() == 0){
    disp->update();
    if(scope_clock->is_done() == 1){
      update_scope();
      scope_clock->reset();
    }
    if(reloading == 1){
      if(reload_clock->is_done() == 1){
        int r = reload();
        if(r == 0){
          reload_clock->reset();
        }
        else{
          reloading = 0;
        }
      }
    }
    if(target_clock->is_done() == 1){
      set_target();
      target_clock -> reset();
      if(reloading == 1){
        scope->remove_scope();
      }
    }
    
  }
  free (game_clock);
  free (scope_clock);
  free (target_clock);
}
void Game::set_target(){
  scope->remove_scope();
  new Target();
  scope->set_scope();
}
//Function for left button to trigger relaoding sequence
void left(){
  cli();
  reloading = 1;
  sei();
}
//Function for right button to trigger fire sequence
void shoot(){
  cli();
  if(reloading == 0){
    if(ammo->fire() == 1){
      //when fired action
      disp->invert_screen();
      disp->update();
      delay(100);
      disp->invert_screen();
      int target_num = tl->is_hit(scope->get_x(),scope->get_y());
      if(target_num != -1){
        tl->target_hit(target_num);
      }
      disp->update();
    }
  }
  sei();
}
int Game::reload(){
  scope->remove_scope();
  disp->update();
  if(ammo->get_remaining() == total_rounds){
    scope->set_scope();
    disp->update();
    return 1;
  }
  ammo->set_rounds(ammo->get_remaining() + 1);
  return 0;
}
void Game::update_scope(){
  scope->update_scope();
}
void Game::set_lights(int num){
  ammo -> set_rounds(num);
}
