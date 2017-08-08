#define ROWS 8
#define COLS 7

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel panel = Adafruit_NeoPixel(56, 13, NEO_GRB + NEO_KHZ800);

bool show_shape[ROWS];
uint32_t colors[ROWS] = {
  panel.Color(0, 255, 255),   //teal - first button
  panel.Color(255, 0, 0),     //red
  panel.Color(0, 0, 255),     //blue
  panel.Color(255, 65, 0),    //orange
  panel.Color(100, 0, 255),   //purple
  panel.Color(255, 125, 0),   //yellow
  panel.Color(255, 0, 0),     //red - there are two reds
  panel.Color(0, 255, 0)      //green
};
int grid[ROWS][COLS];       // actual addresses of serpentine patterned addressable LEDs

void setup() {
  
  // fill the grid arraw\y with addresses
  for(int row=0; row<ROWS; row++){
    // even rows
    for(int column=0; column<COLS; column+=2){
      grid[row][column]=row*ROWS+column;
    }
    // odd rows
    for(int column=1; column<COLS; column=+2){
      grid[row][column]=(row+1)*ROWS-column-1;
    }
  }
  
  // Initialize the panel
  panel.begin();
  panel.show();

  // Setup the 8 buttons
  for(int i=2; i<10; i++){
    pinMode(i, INPUT_PULLUP);
  }
  bool startup = true;
  while(startup){
    all_random();
    delay(250);
    for(int i=2; i<10; i++){
      if(digitalRead(i) == LOW){
        startup = false;
      }
    }
  }
  panel.clear();
  panel.show();
}

void loop() {
  check_buttons();
  display_colors();
}

void all_random(){
  for(int i=0;i<56;i++){
    panel.setPixelColor(i, random(254), random(254), random(254));
  }
  panel.show();
}

void check_buttons(){
  for(int i=0; i<8; i++){
      if(digitalRead(i+2) == LOW){
        show_shape[i] = true;
      }
      else{
        show_shape[i] = false;
      }
    }
}

void display_colors(){
  for(int color=0; color<ROWS; color++){
    for(int pixel = 0; pixel < 7; pixel++){
      if(show_shape[color]){
        panel.setPixelColor(grid[color][pixel],colors[color]);
      }
      else{
        panel.setPixelColor(grid[color][pixel],0,0,0);
      }
    }
  }
  panel.show();
}

