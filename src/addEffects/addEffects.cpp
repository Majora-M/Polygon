#include <Arduino.h>
#include <FastLED.h>
#include <main.h>
#include "rainbow/rainbow.h"

void addGlitter(fract8 chanceOfGlitter)
{
    if (random8() < chanceOfGlitter)
    {
        leds[random16(NUM_LEDS)] += CRGB::White;
    }
}