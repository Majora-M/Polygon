#include <Arduino.h>
#include <FastLED.h>
#include <main.h>
#include "rainbow/rainbow.h"
#include "palettes/palettes.h"
#include "addEffects/addEffects.h"

uint8_t faces = 3;

uint8_t sinelon_bpm_slow = 20;
uint8_t sinelon_bpm_med = 40;
uint8_t sinelon_bpm_fast = 60;

uint8_t rainbow_delta_hue_wide = 7;
uint8_t rainbow_delta_hue_med = 10;
uint8_t rainbow_delta_hue_short = 15;

uint8_t bpm_trail_long = 5;
uint8_t bpm_trail_med = 10;
uint8_t bpm_trail_short = 20;

void tri_sinelon_chase()
{
    // 3 colored dots sweeping the whole triangle, starting in each corner
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t pos = beatsin16(sinelon_bpm_slow, 0, NUM_LEDS - 1);
    for (uint8_t i = 0; i < faces; i++)
    {
        leds[mod8(pos + i * NUM_LEDS_THIRD, NUM_LEDS)] += CHSV(gHue * 2, 255, 192);
    }
}

void tri_sinelon_circular()
{
    // 3 colored dots sweeping their own side, starting in each corner
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t pos = beatsin16(sinelon_bpm_med, 0, NUM_LEDS_THIRD - 1);
    for (uint8_t i = 0; i < faces; i++)
    {
        leds[pos + i * NUM_LEDS_THIRD] += CHSV(gHue * 2, 255, 192);
    }
}

void tri_sinelon_sym_radial()
{
    // 6 colored dots sweeping half side, starting in each corner
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t pos = beatsin16(sinelon_bpm_fast, 0, NUM_LEDS_THIRD - 1);
    for (uint8_t i = 0; i < faces; i++)
    {
        leds[mod8(pos + 2 * i * NUM_LEDS_SIXTH, NUM_LEDS)] += CHSV(gHue * 2, 255, 192);
        leds[mod8(NUM_LEDS - 1 - (pos + 2 * i * NUM_LEDS_SIXTH), NUM_LEDS)] += CHSV(gHue * 2, 255, 192);
    }
}

void tri_sinelon_sym_axial()
{
    // 2 colored dots sweeping half the triangle, starting at summit
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t pos = beatsin16(sinelon_bpm_med, 0, NUM_LEDS_HALF - 1);
    leds[pos] += CHSV(gHue * 2, 255, 192);
    leds[NUM_LEDS - 1 - pos] += CHSV(gHue * 2, 255, 192);
}

void tri_bpm_chase()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = gBpm;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin16(BeatsPerMinute, 64, 255);
    for (uint8_t i = 0; i < NUM_LEDS; i++)
    { // 9948
        leds[i] = ColorFromPalette(
            palette,
            gHue + (i * 2),
            beat - gHue + (i * bpm_trail_long));
    }
}

void tri_bpm_sym_radial()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = gBpm;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin16(BeatsPerMinute, 64, 255);
    for (uint8_t i = 0; i < faces; i++)
        for (uint8_t j = 0; j < NUM_LEDS_SIXTH; j++)
        {
            leds[j + (2 * i * NUM_LEDS_SIXTH)] = ColorFromPalette(
                palette,
                gHue + (j * 2),
                beat - gHue + (j * bpm_trail_short));
            leds[NUM_LEDS - 1 - (j + 2 * i * NUM_LEDS_SIXTH)] = ColorFromPalette(
                palette,
                gHue + (j * 2),
                beat - gHue + (j * bpm_trail_short));
        }
}

void tri_bpm_sym_axial()
{
    // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
    uint8_t BeatsPerMinute = gBpm;
    CRGBPalette16 palette = PartyColors_p;
    uint8_t beat = beatsin16(BeatsPerMinute, 64, 255);
    for (uint8_t i = 0; i < NUM_LEDS_HALF; i++)
    {
        leds[i] = ColorFromPalette(
            palette,
            gHue + (i * 2),
            beat - gHue + (i * bpm_trail_med));
        leds[NUM_LEDS - 1 - i] = ColorFromPalette(
            palette,
            gHue + (i * 2),
            beat - gHue + (i * bpm_trail_med));
    }
}

void tri_confetti_circular()
{
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(leds, NUM_LEDS, 10);
    uint8_t pos = random16(NUM_LEDS);
    leds[pos] += CHSV(gHue + random8(64), 200, 255);
}

void tri_confetti_axial()
{
    // random colored speckles with axial symmetry that blink in and fade smoothly
    fadeToBlackBy(leds, NUM_LEDS, 10);
    uint8_t pos = random16(NUM_LEDS_HALF);
    uint16_t val = gHue + random8(64);
    leds[pos] += CHSV(val, 200, 255);
    leds[NUM_LEDS - 1 - pos] += CHSV(val, 200, 255);
}

void tri_rainbow_chase()
{
    // FastLED's built-in rainbow generator
    for (uint8_t i = 0; i < faces; i++)
    {
        nng_fill_rainbow(leds, i * NUM_LEDS_THIRD, NUM_LEDS_THIRD, gHue, rainbow_delta_hue_med, false);
    }
}

void tri_rainbow_circular()
{
    // FastLED's built-in rainbow generator
    fill_rainbow_circular(leds, NUM_LEDS, gHue, rainbow_delta_hue_med);
}

void tri_rainbow_sym_radial()
{
    for (uint8_t i = 0; i < 6; i++)
    {
        nng_fill_rainbow(leds, i * NUM_LEDS_SIXTH, NUM_LEDS_SIXTH, gHue, rainbow_delta_hue_wide, mod8(i, 2));
    }
}

void tri_rainbow_sym_axial()
{
    for (uint8_t i = 0; i < 2; i++)
    {
        nng_fill_rainbow(leds, i * NUM_LEDS_HALF, NUM_LEDS_HALF, gHue, rainbow_delta_hue_wide, mod8(i, 2));
    }
}
