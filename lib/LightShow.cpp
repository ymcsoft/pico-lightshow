//
// Created by Yuri Moiseyenko on 2024-10-14.
//
#include "LightShow.h"
#include "br_iterator.h"
#include "range.h"

LightShow::LightShow() : LightShow(NUMPIXELS, PIN, NEO_GBR + NEO_KHZ800) {};

LightShow::LightShow(uint16_t numPixels, uint16_t pin, uint16_t type) {
    this->pixels = new Adafruit_NeoPixel(numPixels, pin, NEO_RGB + NEO_KHZ800);
}

LightShow::~LightShow() {
    delete this->pixels;//cleanup Adafruit_NeoPixel structure
}

void LightShow::glowing(struct PIXEL_COLOR *c, uint16_t delay) {
    pixels->setBrightnessFunctions(adjust,adjust,adjust,adjust);
    pixels->clear(); // Set all pixel colors to 'off'
    printf("cleared pixels 1, level = %d\n",level);

    for(int i=0; i < pixels->numPixels(); i++) { // For each pixel...
        pixels->setPixelColor(i,Adafruit_NeoPixel::Color(c->r, c->g, c->b));

        pixels->show();   // Send the updated pixel colors to the hardware.

        sleep_ms(DELAYVAL); // Pause before next pass through loop
    }
    //set control brightness down and up
    for(int i : range(3)) setBrightness(delay, i % 2);
    level = 0; //set default brightness level
}

void LightShow::setBrightness(uint16_t delay, bool up) {
    br_iterator iter(up);
    printf("Starting LightShow::setBrightness up=%d",up);
    level = iter.begin();
    for(int i=0; i < 255 ; i++) {
        level = iter.next();
        printf("brightness level=%d", level);
        pixels->setBrightnessFunctions(adjust, adjust, adjust, adjust);
        pixels->show();
        sleep_ms(delay);
    }
    level = iter.end();

    printf("Ending LightShow::setBrightness level=%d",level);
}

void LightShow::colorWipe(struct PIXEL_COLOR *color, uint32_t wait) {
    for(uint16_t i=0; i<pixels->numPixels(); i++) {
        pixels->setPixelColor(i, Adafruit_NeoPixel::Color(color->r ,color->g, color->b));
        pixels->show();
        sleep_ms(wait);
    }
}

void LightShow::colorWipe(struct PIXEL_COLOR* (* colorFunc)(), uint32_t wait) {
    for(uint16_t i=0; i<pixels->numPixels(); i++) {
        PIXEL_COLOR* color = colorFunc();
        pixels->setPixelColor(i, Adafruit_NeoPixel::Color(color->r ,color->g, color->b));
        pixels->show();
        sleep_ms(wait);
    }
}

void LightShow::theaterChase(struct PIXEL_COLOR* color, uint32_t wait) {
    for (int j=0; j<10; j++) {  //do 10 cycles of chasing
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, Adafruit_NeoPixel::Color(color->r, color->g, color->b));    //turn every third pixel on
            }
            pixels->show();

            sleep_ms(wait);

            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}

void LightShow::rainbow(uint32_t wait) {
    uint16_t i, j;

    for(j=0; j<256; j++) {
        for(i=0; i<pixels->numPixels(); i++) {
            pixels->setPixelColor(i, wheel((i+j) & 255));
        }
        pixels->show();
        sleep_ms(wait);
    }
}

void LightShow::rainbowChase(uint32_t wait) {
    uint16_t i, j;

    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< pixels->numPixels(); i++) {
            pixels->setPixelColor(i, wheel(((i * 256 / pixels->numPixels()) + j) & 255));
        }
        pixels->show();
        sleep_ms(wait);
    }
}

void LightShow::theaterChaseRainbow(uint32_t wait) {
    for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, wheel( (i+j) % 255));    //turn every third pixel on
            }
            pixels->show();

            sleep_ms(wait);

            for (uint16_t i=0; i < pixels->numPixels(); i=i+3) {
                pixels->setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}