#include <random>
#include "LightShow.h"


// Which pin on the Pico is connected to the NeoPixels?
#define NEOPIXEL_PIN        0 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUM_PIXELS 150 // Popular NeoPixel ring size

#define DELAY_VAL 100

PIXEL_COLOR pixelColor;
std::uniform_int_distribution<> distr(0, 255);
std::random_device dev;
std::mt19937 gen(dev());

PIXEL_COLOR* randomColor(void);

int main () {
    stdio_init_all();
    PIXEL_COLOR pumpkin(255, 45, 0);
    LightShow lightShow(NUM_PIXELS, NEOPIXEL_PIN);
    while(1) {
        lightShow.glowing(&pumpkin);
        sleep_ms(5000);
        lightShow.colorWipe(randomColor);
        sleep_ms(5000);
        lightShow.theaterChase(&pumpkin, DELAY_VAL);
        sleep_ms(5000);
        lightShow.rainbow();
        sleep_ms(5000);
        lightShow.rainbowChase();
        sleep_ms(5000);
        lightShow.theaterChaseRainbow();
    }
}

PIXEL_COLOR* randomColor(void) {
    pixelColor.r = distr(gen);
    pixelColor.g = distr(gen);
    pixelColor.b = distr(gen);
    return &pixelColor;
}