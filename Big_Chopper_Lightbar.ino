#include <Adafruit_NeoPixel.h>

uint8_t lightBarPosition = 0;
uint8_t lightBarBrightness = 255;
bool lightBarDirection = true;

uint8_t highlightBrightness = 180;
uint8_t lowlightBrightness = 10;

Adafruit_NeoPixel *neoPixel_lightbar;
neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;

void loopLightbar() {

  uint32_t highlightColor = neoPixel_lightbar->Color(highlightBrightness, 0, 0);
  uint32_t lowlightColor = neoPixel_lightbar->Color(lowlightBrightness, 0, 0);

  for (uint8_t i = 0; i < 19; i++) {
    if (i == lightBarPosition) {
      neoPixel_lightbar->setPixelColor(i, highlightColor);
    } else {
      neoPixel_lightbar->setPixelColor(i, lowlightColor);
    }
  }
  if (lightBarDirection) {
    lightBarPosition = lightBarPosition + 1;
  } else {
    lightBarPosition = lightBarPosition - 1;
  }

  if (lightBarPosition >= 18) {
    lightBarDirection = false;
  } else if (lightBarPosition <= 0) {
    lightBarDirection = true;
  }

  neoPixel_lightbar->show();
}

void setup() {
  // put your setup code here, to run once:

  neoPixel_lightbar = new Adafruit_NeoPixel(19, 9, pixelFormat);
  neoPixel_lightbar->setBrightness(lightBarBrightness);
  neoPixel_lightbar->begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  loopLightbar();
  delay(200);
}
