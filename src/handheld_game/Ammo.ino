/*
 * Ammo class tracks the shots used.  Also controlls LEDs to visually display shots used.
 * Contains option for 5 shot round or 3 shot round.
 */
#include "Ammo.h"
#include "Screen.h"

Ammo::Ammo(int r){
  pinMode(shot_1, OUTPUT);
  pinMode(shot_2, OUTPUT);
  pinMode(shot_3, OUTPUT);
  pinMode(shot_4, OUTPUT);
  pinMode(shot_5, OUTPUT);
  total = r;
}
Ammo::~Ammo(){
  
}
int Ammo::fire(){
  if(rounds_left > 0){
    rounds_left = rounds_left - 1;
    update();
    return 1;
  }
  else{
    return 0;
  }
}
void Ammo::reload(){
  while(rounds_left < total){
    delay(500);
    rounds_left++;
    update();
  }
  delay(200);
}
void Ammo::update(){
  digitalWrite(shot_1,LOW);
  digitalWrite(shot_2,LOW);
  digitalWrite(shot_3,LOW);
  digitalWrite(shot_4,LOW);
  digitalWrite(shot_5,LOW);
  if(total == 5){
    if(rounds_left >= 1){
      digitalWrite(shot_1, HIGH);
    }
    if(rounds_left >= 2){
      digitalWrite(shot_2, HIGH);
    }
    if(rounds_left >= 3){
      digitalWrite(shot_3, HIGH);
    }
    if(rounds_left >= 4){
      digitalWrite(shot_4, HIGH);
    }
    if(rounds_left >= 5){
      digitalWrite(shot_5, HIGH);
    }
  }
  if(total == 3){
    if(rounds_left >= 1){
      digitalWrite(shot_1, HIGH);
    }
    if(rounds_left >= 2){
      digitalWrite(shot_2, HIGH);
      digitalWrite(shot_3, HIGH);
    }
    if(rounds_left >= 3){
      digitalWrite(shot_4, HIGH);
      digitalWrite(shot_5, HIGH);
    }
  }
}
int Ammo::get_remaining(){
  return rounds_left;
}
void Ammo::set_rounds(int num){
  rounds_left = num;
  update();
}
