#include <random>
#include "LightShow.h"


// Which pin on the Pico is connected to the NeoPixels?
#define NEOPIXEL_PIN        0 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Pico?
#define NUM_PIXELS 100

#define DELAY_VAL 100

PIXEL_COLOR pixelColor;
std::uniform_int_distribution<> distr(0, 255);
std::random_device dev;
std::mt19937 gen(dev());

PIXEL_COLOR* randomColor(void);

const uint32_t PAUSE_TIME = 5000;

int main () {
    stdio_init_all();
    PIXEL_COLOR pumpkin(255, 45, 0);
    LightShow lightShow(NUM_PIXELS, NEOPIXEL_PIN, NEO_RBG + NEO_KHZ800);
    while(1) {
        lightShow.glowing(&pumpkin);
        sleep_ms(PAUSE_TIME);
        lightShow.colorWipe(&pumpkin);
        sleep_ms(PAUSE_TIME);
        lightShow.colorWipe(randomColor);
        sleep_ms(PAUSE_TIME);
        lightShow.theaterChase(&pumpkin, DELAY_VAL);
        sleep_ms(PAUSE_TIME);
        lightShow.rainbow();
        sleep_ms(PAUSE_TIME);
        lightShow.rainbowChase();
        sleep_ms(PAUSE_TIME);
        lightShow.theaterChaseRainbow(DELAY_VAL);
    }
}

PIXEL_COLOR* randomColor(void) {
    pixelColor.r = distr(gen);
    pixelColor.g = distr(gen);
    pixelColor.b = distr(gen);
    return &pixelColor;
}