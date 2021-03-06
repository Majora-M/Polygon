#include <Arduino.h>
#include <FastLED.h>
#include <main.h>
#include "debug/debug.h"
#include "addEffects/addEffects.h"
#include "rainbow/rainbow.h"
#include "triangles/triangles.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

CRGB leds[NUM_LEDS];

// To flash : use PlatformIO Upload (botton bar) and press 'boot' on board

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

// executed once at start
void setup()
{
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  // FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
// SimplePatternList gPatterns = {rainbow, nngRainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm};

// DEBUG PATTERNS
// SimplePatternList gPatterns = {
//     tri_bpm_chase,
//     tri_bpm_sym_radial,
//     tri_bpm_sym_axial,
//     tri_sinelon_chase,
//     tri_sinelon_circular,
//     tri_sinelon_sym_radial,
//     tri_sinelon_sym_axial,
//     tri_rainbow_chase,
//     tri_rainbow_circular,
//     tri_rainbow_sym_radial,
//     tri_rainbow_sym_axial,
//     tri_confetti,
// };

SimplePatternList gPatterns = {
    tri_bpm_chase,
    tri_sinelon_sym_radial,
    tri_rainbow_circular,
    tri_bpm_sym_axial,
    tri_sinelon_chase,
    tri_confetti_circular,
    tri_confetti_axial,
    tri_rainbow_sym_radial,
    tri_sinelon_sym_axial,
    tri_bpm_sym_radial,
    tri_sinelon_circular,
    tri_rainbow_sym_axial,
};

// TODO list of palettes ?
// typedef TProgmemRGBPalette16[];
// TProgmemRGBPalette16 gPalettes = {PartyColors_p, CloudColors_p};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0;                  // rotating "base color" used by many of the patterns
uint8_t gBpm = 120;
uint8_t gBpmMin = 80;
uint8_t gBpmMax = 140;
uint32_t analogValue = 0;

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

// TODO cycle through list of palettes
// void nextPalette()
// {
//   // add one to the current pattern number, and wrap around at the end
//   gCurrentPaletteNumber = (gCurrentPaletteNumber + 1) % ARRAY_SIZE(gPalettes);
// }

// executed infinitely after setup
void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  analogValue = analogRead(34); // GIOP36
  gBpm = map(analogValue, 0, 4095, gBpmMin, gBpmMax);

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS(20) { gHue++; }  // slowly cycle the "base color" through the rainbow
  EVERY_N_SECONDS(6) { nextPattern(); } // change patterns periodically
}