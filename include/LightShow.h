//
// Created by Yuri Moiseyenko on 2024-10-14.
//

#ifndef PICO_LIGHTSHOW_LIGHTSHOW_H
#define PICO_LIGHTSHOW_LIGHTSHOW_H
#include <cstdio>
#include "pico/stdio.h"
#include "pico/time.h"
#include "Adafruit_NeoPixel.hpp"
// Which pin on the Pico is connected to the NeoPixels?
#define PIN        0 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 50 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels
#define CYCLEDELAY 12 // Time to wait after a cycle
// static declarations
static uint8_t level = 0 ;

struct PIXEL_COLOR {
    uint8_t r, g, b;
    PIXEL_COLOR(uint8_t r=0, uint8_t g=0, uint8_t b=0) {
        this->r = r;
        this->b = b;
        this->g = g;
    }
};

static uint8_t adjust (uint8_t value);

class LightShow {
public:
    LightShow();
    LightShow(uint16_t numPixels, uint16_t pin, uint16_t type=NEO_GBR + NEO_KHZ800);
    virtual ~LightShow();
    void glowing(struct PIXEL_COLOR* pixelColor, uint16_t delay=CYCLEDELAY);
    void colorWipe(struct PIXEL_COLOR *color, uint32_t wait=CYCLEDELAY);
    void colorWipe(struct PIXEL_COLOR* (* colorFunc)(void), uint32_t wait=CYCLEDELAY);
    void theaterChase(struct PIXEL_COLOR* color, uint32_t wait=CYCLEDELAY);
    void rainbow(uint32_t wait=DELAYVAL);
    void rainbowChase(uint32_t wait=DELAYVAL);
    void theaterChaseRainbow(uint32_t wait=CYCLEDELAY);
private:
    Adafruit_NeoPixel* pixels;
    // Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
    static inline uint32_t wheel(uint8_t wheelPos) {
        wheelPos = 255 - wheelPos;
        if(wheelPos < 85) {
            return Adafruit_NeoPixel::Color(255 - wheelPos * 3, 0, wheelPos * 3);
        }
        if(wheelPos < 170) {
            wheelPos -= 85;
            return Adafruit_NeoPixel::Color(0, wheelPos * 3, 255 - wheelPos * 3);
        }
        wheelPos -= 170;
        return Adafruit_NeoPixel::Color(wheelPos * 3, 255 - wheelPos * 3, 0);
    }

    void setBrightness(uint16_t delay, bool up=true);
};

// static functions
static uint8_t adjust (uint8_t value) {
    if (level == 0) return value ;
    return ((value * neopixels_gamma8(level)) >> 8) ;
};

#endif //PICO_LIGHTSHOW_LIGHTSHOW_H
