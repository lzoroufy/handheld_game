#include <SparkFun_MMA8452Q.h>
#include "Screen.h"
#include "Game.h"

Screen *disp = new Screen();
int right_button = 15;
int left_button = 16;

void shoot();
void left();
volatile int reloading;

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(right_button), shoot, RISING);
  attachInterrupt(digitalPinToInterrupt(left_button), left, RISING);
}
int rbp = 0;
int lbp = 0;
long g;
long t;
int r;
int a;
int score = 0;
void loop() {
  disp->update();
  disp->clear();
  disp->update();
  Game *game = new Game(60000,1000,5,0);
  score = game->run_game();
  delete (game);
  display_score();
  delay(10000);
}
void display_score(){
  disp -> clear();
  disp -> update();
  disp->led_on();
  int j = 0;
  int i;
  for(i = 0; i<5; i++){
    disp->displayMap[j] = disp->ASCII[51][i];
    j++;
  }
  disp->update();
  delay(1000);
  for(i = 0; i<5; i++){
    disp->displayMap[j] = disp->ASCII[35][i];
    j++;
  }
  disp->update();
  delay(1000);
  for(i = 0; i<5; i++){
    disp->displayMap[j] = disp->ASCII[47][i];
    j++;
  }
  disp->update();
  delay(1000);
  for(i = 0; i<5; i++){
    disp->displayMap[j] = disp->ASCII[50][i];
    j++;
  }
  disp->update();
  delay(1000);
  for(i = 0; i<5; i++){
    disp->displayMap[j] = disp->ASCII[37][i];
    j++;
  }
  disp->update();
  delay(1000);
  for(i = 0; i<5; i++){
    j++;
  }
  disp->update();
  delay(1000);
  int tens = score/10;
  for(i = 0; i<5; i++){
    disp->displayMap[j] = disp->ASCII[tens+16][i];
    j++;
  }
  disp->update();
  delay(1000);
  tens = tens*10;
  int ones = score-tens;
  for(i = 0; i<5; i++){
    disp->displayMap[j] = disp->ASCII[ones+16][i];
    j++;
  }
  disp->update();
}
