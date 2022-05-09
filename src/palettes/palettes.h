#pragma once
#include <Arduino.h>
#include <FastLED.h>

void nng_fill_rainbow(struct CRGB *pFirstLED,
                      int firstLed,
                      int numToFill,
                      uint8_t initialhue,
                      uint8_t deltahue,
                      bool reverse);
