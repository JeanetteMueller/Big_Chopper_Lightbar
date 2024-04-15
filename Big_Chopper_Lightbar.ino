// Chopper Lightbar 1.1 for Chopper Logics v1.2 printed-droid.com
// Jeanette Müller
// 2024.04.11

#include <Adafruit_NeoPixel.h>

#define LightBarPin 9
#define LightBarLedCount 19
#define Eye1Pin 10
#define Eye1LedCount 7
#define Eye2Pin 11
#define Eye2LedCount 7
#define Eye3Pin 12
#define Eye3LedCount 7
#define PeriscopePin 13
#define PeriscopeLedCount 1

// TIME
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;

//Lightbar Properties
uint8_t lightBarPosition = 0;
uint8_t lightBarBrightness = 255;
enum lightBarDirection {
  up,
  down
};
lightBarDirection currentLightBarDirection = up;
uint8_t highlightBrightness = 180;
uint8_t lowlightBrightness = 10;
uint8_t lightBarRefreshrate = 200;

//Eyes
uint8_t eyesBrightness = 255;

//Periscope
uint8_t periscopeBrightness = 255;

//Neopixel Instances
neoPixelType pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel *neoPixel_lightbar = new Adafruit_NeoPixel(LightBarLedCount, LightBarPin, pixelFormat);
Adafruit_NeoPixel *neoPixel_eye1 = new Adafruit_NeoPixel(Eye1LedCount, Eye1Pin, pixelFormat);
Adafruit_NeoPixel *neoPixel_eye2 = new Adafruit_NeoPixel(Eye2LedCount, Eye2Pin, pixelFormat);
Adafruit_NeoPixel *neoPixel_eye3 = new Adafruit_NeoPixel(Eye3LedCount, Eye3Pin, pixelFormat);
Adafruit_NeoPixel *neoPixel_periscope = new Adafruit_NeoPixel(PeriscopeLedCount, PeriscopePin, pixelFormat);

//Colors
uint32_t highlightColor = neoPixel_lightbar->Color(highlightBrightness, 0, 0);
uint32_t lowlightColor = neoPixel_lightbar->Color(lowlightBrightness, 0, 0);
uint32_t eye1Color = neoPixel_eye1->Color(0, 0, 128);
uint32_t eye2Color = neoPixel_eye2->Color(0, 0, 128);
uint32_t eye3Color = neoPixel_eye3->Color(0, 0, 128);
uint32_t periscopeColor = neoPixel_periscope->Color(255, 0, 0);

void loopLightbar() {
  for (uint8_t i = 0; i < LightBarLedCount; i++) {
    if (i == lightBarPosition) {
      neoPixel_lightbar->setPixelColor(i, highlightColor);
    } else {
      neoPixel_lightbar->setPixelColor(i, lowlightColor);
    }
  }
  neoPixel_lightbar->show();

  //change parameter for next loop
  if (currentLightBarDirection == up) {
    lightBarPosition = lightBarPosition + 1;
  } else {
    lightBarPosition = lightBarPosition - 1;
  }

  if (lightBarPosition >= (LightBarLedCount - 1)) {
    currentLightBarDirection = down;
  } else if (lightBarPosition <= 0) {
    currentLightBarDirection = up;
  }
}

void loopEyes() {
  for (uint8_t i = 0; i < Eye1LedCount; i++) {
    neoPixel_eye1->setPixelColor(i, eye1Color);
  }
  for (uint8_t i = 0; i < Eye2LedCount; i++) {
    neoPixel_eye2->setPixelColor(i, eye2Color);
  }
  for (uint8_t i = 0; i < Eye3LedCount; i++) {
    neoPixel_eye3->setPixelColor(i, eye3Color);
  }

  neoPixel_eye1->show();
  neoPixel_eye2->show();
  neoPixel_eye3->show();
}

void loopPeriscope() {
  for (uint8_t i = 0; i < PeriscopeLedCount; i++) {
    neoPixel_periscope->setPixelColor(i, periscopeColor);
  }
  neoPixel_periscope->show();
}

void setup() {
  neoPixel_lightbar->setBrightness(lightBarBrightness);
  neoPixel_lightbar->begin();

  neoPixel_eye1->setBrightness(eyesBrightness);
  neoPixel_eye1->begin();

  neoPixel_eye2->setBrightness(eyesBrightness);
  neoPixel_eye2->begin();

  neoPixel_eye3->setBrightness(eyesBrightness);
  neoPixel_eye3->begin();

  neoPixel_periscope->setBrightness(periscopeBrightness);
  neoPixel_periscope->begin();
}

void loop() {
  currentMillis = millis();

  if (currentMillis - previousMillis >= lightBarRefreshrate) {
    previousMillis = currentMillis;
    loopLightbar();
  }

  loopEyes();
  loopPeriscope();
}
