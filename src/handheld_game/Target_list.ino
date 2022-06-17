#include "Target_list.h"
#include "Scope.h"
#include "Target.h"


Target_list::Target_list(int n){
  for(int i = 0; i<84; i++){
    for(int j = 0; j<48; j++){
      target[i][j] = -1;
    }
  }
}
Target_list::~Target_list(){
}
int Target_list::is_available(int x, int y){
  if(target[x][y] == -1){
    return 1;
  }
  return 0;
}
void Target_list::target_added(){
  target_counter++;
}
void Target_list::update_list(int x, int y){
  target[x][y] = target_counter;
}
int Target_list::target_hit(int t){
  scope->remove_scope();
  remove_target(t);
  score++;
  scope->set_scope();
  return -1;
}
void Target_list::remove_target(int t){
  for(int i = 0; i<84; i++){
    for(int j = 0; j<48; j++){
      if(target[i][j] == t){
        target[i][j] = -1;
        disp->remove_pixel(i,j);
      }
    }
  }
}
int Target_list::is_hit(int x, int y){
  return target[x][y];
}
int Target_list::get_score(){
  return score;
}
