#define ROWS 8
#define COLS 7
#define DEBUG 1

#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel panel = Adafruit_NeoPixel(56, 13, NEO_GRB + NEO_KHZ800);

bool show_shape[ROWS];
uint32_t colors[7] = {
  panel.Color(255, 0, 0),     //red
  panel.Color(255, 65, 0),    //orange
  panel.Color(255, 125, 0),   //yellow
  panel.Color(0, 255, 0),     //green
  panel.Color(0, 255, 255),   //teal
  panel.Color(0, 0, 255),     //blue
  panel.Color(100, 0, 255)    //purple
};
int grid[ROWS][COLS];       // actual addresses of serpentine patterned addressable LEDs

int button_color_map[8][2] = {      // index is row
  {3,0},                            // first value is button number
  {5,1},                            // second value is color
  {7,2},
  {9,3},
  {2,4},
  {4,5},
  {6,6},
  {8,0}
};


void setup() {
  
#ifdef DEBUG
  Serial.begin(9600);
#endif
  // fill the grid arraw\y with addresses
  for(int row=0; row<ROWS; row++){
    for(int column=0; column<COLS; column++){
      if(column%2 == 0){
       grid[row][column]=row+ROWS*column;
      }
      else{
       grid[row][column]=ROWS*(column+1)-row-1;
      }
#ifdef DEBUG
      Serial.print(grid[row][column]);
      Serial.print(", ");
#endif
    }
#ifdef DEBUG
    Serial.println(" - end row");
#endif
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
  //test_order();
}

void all_random(){
  for(int i=0;i<56;i++){
    panel.setPixelColor(i, random(254), random(254), random(254));
  }
  panel.show();
}

void check_buttons(){
  for(int i=0; i<8; i++){
      if(digitalRead(button_color_map[i][0]) == LOW){
        show_shape[i] = true;
      }
      else{
        show_shape[i] = false;
      }
    }
}

void display_colors(){
  for(int row=0; row<ROWS; row++){
    if(show_shape[row]){
      for(int column = 0; column < COLS; column++){
        panel.setPixelColor(grid[row][column],colors[button_color_map[row][1]]);
      }
    }
    else{
      for(int column = 0; column < COLS; column++){
        panel.setPixelColor(grid[row][column],0,0,0);
      }
    }
  }
  panel.show();
  delay(10);
}

void test_order(){
  for(int row=0; row<ROWS; row++){
    for(int col = 0; col < COLS; col++){
      panel.setPixelColor(grid[row][col],colors[row]);
      panel.show();
      delay(100);
      panel.setPixelColor(grid[row][col],0,0,0);
      panel.show();
    }
  }
}

