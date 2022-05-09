#include <Arduino.h>
#include <FastLED.h>
#include <main.h>
#include "rainbow/rainbow.h"
#include "palettes/palettes.h"
#include "addEffects/addEffects.h"

void tri_sinelon_circular()
{
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t pos = beatsin16(13, 0, NUM_LEDS - 1);
    for (uint8_t i = 0; i < 3; i++)
    {
        leds[mod8(pos + i * NUM_LEDS_TRI * 2, NUM_LEDS)] += CHSV(gHue, 255, 192);
    }
}

void tri_sinelon_symmetry()
{
    // a colored dot sweeping back and forth, with fading trails
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t pos = beatsin16(30, 0, NUM_LEDS_TRI * 2 - 1);
    for (uint8_t i = 0; i < 3; i++)
    {
        leds[pos + i * NUM_LEDS_TRI * 2] += CHSV(gHue, 255, 192);
    }
}

void tri_bpm()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = 62;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
    for (uint8_t i = 0; i < NUM_LEDS; i++)
    { // 9948
        leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
    }
}

void tri_confetti()
{
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds, NUM_LEDS, 10);
    uint8_t pos = random16(NUM_LEDS);
    leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void tri_rainbow_circular()
{
    // FastLED's built-in rainbow generator
    fill_rainbow_circular(leds, NUM_LEDS, gHue, 7);
}

void tri_rainbow_symmetry()
{
    for (uint8_t i = 0; i < 6; i++)
    {
        nng_fill_rainbow(leds, i * NUM_LEDS_TRI, NUM_LEDS_TRI, gHue, 12, mod8(i, 2));
    }
}
