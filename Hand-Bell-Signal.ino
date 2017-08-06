#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel panel = Adafruit_NeoPixel(56, 13, NEO_GRB + NEO_KHZ800);

bool show_colors[8] = {false, false, false, false, false, false, false, false};
uint32_t colors[8] = {
panel.Color(0, 255, 255),   //teal - first button
panel.Color(255, 0, 0),     //red
panel.Color(0, 0, 255),     //blue
panel.Color(255, 65, 0),   //orange
panel.Color(100, 0, 255),    //purple
panel.Color(255, 125, 0),   //yellow
panel.Color(255, 0, 0),     //red - there are two reds
panel.Color(0, 255, 0)     //green
};
int shapes[8][7] = {
  {5,12,21,28,37,44,53},
  {1,16,17,32,33,48,49},
  {6,11,22,27,38,43,54},
  {2,15,18,31,34,47,50},
  {7,10,23,26,39,42,55},
  {3,14,19,30,35,46,51},
  {8,9,24,25,40,41,56},
  {4,13,20,29,36,45,52}
};

void setup() {
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
        show_colors[i] = true;
      }
      else{
        show_colors[i] = false;
      }
    }
}

void display_colors(){
  for(int color=0; color<8; color++){
    for(int pixel = 0; pixel < 7; pixel++){
      if(show_colors[color]){
        panel.setPixelColor(shapes[color][pixel]-1,colors[color]);
      }
      else{
        panel.setPixelColor(shapes[color][pixel]-1,0,0,0);
      }
    }
  }
  panel.show();
}

