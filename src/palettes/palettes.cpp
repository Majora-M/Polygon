#include <Arduino.h>
#include <FastLED.h>
#include <main.h>

void nng_fill_rainbow(struct CRGB *pFirstLED,
                      int firstLed,
                      int numToFill,
                      uint8_t initialhue,
                      uint8_t deltahue,
                      bool reverse)
{
    CHSV hsv;
    hsv.hue = initialhue;
    hsv.val = 255;
    hsv.sat = 240;
    // TOWARN : i is uint8_t but numToFill is int
    for (uint8_t i = 0; i < numToFill; ++i)
    {
        if (reverse)
        {
            pFirstLED[firstLed + numToFill - 1 - i] = hsv;
        }
        else
        {
            pFirstLED[firstLed + i] = hsv;
        }
        hsv.hue += deltahue;
    }
}
