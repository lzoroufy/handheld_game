#include <SPI.h>
#include "Screen.h"

Screen::Screen(){ 
  pinMode(ss, OUTPUT);
  pinMode(rst, OUTPUT);
  pinMode(dc, OUTPUT);
  pinMode(mosi, OUTPUT);
  pinMode(sclk, OUTPUT);
  pinMode(led, OUTPUT);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);

  reset();
  clear();
}
Screen::~Screen(){
}
void Screen::led_on(){
  digitalWrite(led,HIGH);
  LED_status = 1;
}
void Screen::led_off(){
  digitalWrite(led,LOW);
  LED_status = 0;
}
void Screen::led_dim(int d){
  analogWrite(led,d);
  LED_status = 1;
}

void Screen::led_switch(){
  if(LED_status == 1){
    led_off();
  }
  else{
    led_on();
  }
}
void Screen::write(byte data){
  //Tell the LCD that we are writing either to data or a command
  digitalWrite(dc, HIGH);

  //Send the data
  digitalWrite(ss, LOW);
  SPI.transfer(data);
  digitalWrite(ss, HIGH);
}
void Screen::command(byte data){
  //Tell the LCD that we are writing either to data or a command
  digitalWrite(dc, LOW);

  //Send the data
  digitalWrite(ss, LOW);
  SPI.transfer(data);
  digitalWrite(ss, HIGH);
}
void Screen::goto_XY(int x, int y){
  command(0x80 | x);
  command(0x40 | y);
}
void Screen::update(){
  goto_XY(0, 0);
  for(int i = 0; i < 504; i++){
    write(displayMap[i]);
  }
}
void Screen::clear(){
  goto_XY(0, 0);
  for(int i = 0; i < 504; i++){
    displayMap[i] = 0x00;
  }
  update();
}
void Screen::hide(){
  goto_XY(0, 0);
  for(int i = 0; i < 504; i++){
    write(0x00);
  }
}
void Screen::invert_screen(){
  for(int i = 0; i < 84; i++){
    for(int j = 0; j < 48; j++){
      invert_pixel(i,j);
    }
  }
}
void Screen::reset(){
  digitalWrite(rst,LOW);
  digitalWrite(rst,HIGH);
  command(0x21); //Tell LCD extended commands follow
  command(0xB0); //Set LCD Vop (Contrast)
  command(0x04); //Set Temp coefficent
  command(0x14); //LCD bias mode 1:48 (try 0x13)
  //We must send 0x20 before modifying the display control mode
  command(0x20);
  command(0x0C); //Set display control, normal mode.
}
void Screen::set_char(char c, int x, int y){
  byte column; // temp byte to store character's column bitmap
  for (int i=0; i<5; i++) // 5 columns (x) per character
  {
    column = ASCII[c - 0x20][i];
    for (int j=0; j<8; j++) // 8 rows (y) per character
    {
      if (column & (0x01 << j)) // test bits to set pixels
        set_pixel(x+i, y+j);
      else
        remove_pixel(x+i, y+j);
    }
  }
}
void Screen::set_pixel(int x, int y){
  if(x>=0 && x<84 && y>=0 && y<48){
    y = 47 - y;
    byte shift = y % 8;
    displayMap[x + (y/8)*84] |= 1<<shift;
  }
}
void Screen::remove_pixel(int x, int y){
  if(x>=0 && x<84 && y>=0 && y<48){
    y = 47 - y;
    byte shift = y % 8;
    displayMap[x + (y/8)*84] &= ~(1<<shift);
  }
}
void Screen::invert_pixel(int x, int y){
  if(is_black(x,y)){
    remove_pixel(x,y);
  }
  else{
    set_pixel(x,y);
  }
}
boolean Screen::is_black(int x, int y){
  if(x>=0 && x<84 && y>=0 && y<48){
    y = 47 - y;
    byte shift = y % 8;
    byte target = displayMap[x + (y/8)*84];
    target &= 1<<shift;
    if(target == (1<<shift)){
      return 1;
    }
  }
  return 0;
}
