#include <Adafruit_NeoPixel.h>
#define PANELPIN 6

Adafruit_NeoPixel panel = Adafruit_NeoPixel(56, PANELPIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // Initialize the panel
  panel.begin();
  panel.show();

  // show some random colors
}

void loop() {
  // put your main code here, to run repeatedly:
  random();
  delay(250);
}

void random(){
  for( i=0;i<56;i++){
    panel.setpixelcolor(random(254), random(254, random(254));
  }
  panel.show();
}

