#include <Adafruit_NeoPixel.h>

#define PIN        18
#define NUMPIXELS 2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500


void setup() {
  pinMode(32, OUTPUT);
  pixels.begin();
  pixels.clear();
  tone(32, 300);
}

void loop() {

    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    pixels.show();
    delay(DELAYVAL);

    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    pixels.show();
    delay(DELAYVAL);

    pixels.setPixelColor(0, pixels.Color(0, 0, 150));
    pixels.show();
    delay(DELAYVAL);
  
}