#include <Adafruit_NeoPixel.h>
#define PIN        6
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500


void setup() {
  pixels.begin();

}

void loop() {
  pixels.clear();

    pixels.setPixelColor(1, pixels.Color(150, 0, 0));
    pixels.show();
    delay(DELAYVAL);

    pixels.setPixelColor(1, pixels.Color(0, 150, 0));
    pixels.show();
    delay(DELAYVAL);

    pixels.setPixelColor(1, pixels.Color(0, 0, 150));
    pixels.show();
    delay(DELAYVAL);
  }
}