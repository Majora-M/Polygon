#pragma once
#include <Arduino.h>
#include <FastLED.h>

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

// Specs :
// 30 LED / m

// DATA_PIN = 13 (green wire) on our board
#define DATA_PIN 13
// We are not working with leds with clocks
//#define CLK_PIN   4
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
// The 1m strip is 90 LEDs long
#define NUM_LEDS 90
#define NUM_LEDS_TRI 15

extern CRGB leds[NUM_LEDS];

// max : 255
// reasonable : 60
// medium : 120 (500mA)
#define BRIGHTNESS 120
#define FRAMES_PER_SECOND 120

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

extern uint8_t gCurrentPatternNumber; // Index number of which pattern is current
extern uint8_t gHue;                  // rotating "base color" used by many of the patterns
