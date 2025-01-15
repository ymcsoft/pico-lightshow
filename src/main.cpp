#include <random>
#include "LightShow.h"
#include "hardware/gpio.h"
// Which pin on the Pico is connected to the NeoPixels?
#define NEOPIXEL_PIN        2 // The first port using GP2
#define NEOPIXEL2_PIN       8 // The second port using GP8

PIXEL_COLOR pixelColor;
std::uniform_int_distribution<> distr(0, 255);
std::uniform_int_distribution<> christmas_distr(0, 4);
std::random_device dev;
std::mt19937 gen(dev());

const uint32_t DELAY_VAL = std::stoi(DELAY);
const uint32_t PAUSE_TIME = std::stoi(PAUSE);
static uint8_t level = 0 ;
static uint8_t level2 = 0;
const uint16_t CONTROL_PIN = 13;

static uint8_t adjust (uint8_t value);
static uint8_t adjust2 (uint8_t value);
PIXEL_COLOR* randomColor(void);
uint16_t getType();

void vPixelOneTask(void*);
void vPixelTwoTask(void*);

int main () {
    stdio_init_all();
    // init control pin and turn it on
    gpio_init(CONTROL_PIN);
    gpio_set_dir(CONTROL_PIN, GPIO_OUT);
    gpio_put(CONTROL_PIN, true);
    TaskHandle_t task;
    xTaskCreate(vPixelOneTask, "Pico Show 1", configMINIMAL_STACK_SIZE, NULL, NEOPIXEL_TASK_PRIORITY, &task);
#if NO_SYS && configUSE_CORE_AFFINITY && configNUMBER_OF_CORES > 1
    // we must bind the main task to one core (well at least while the init is called)
    // (note we only do this in NO_SYS mode, because cyw43_arch_freertos
    // takes care of it otherwise)
    vTaskCoreAffinitySet(task, 1);
#endif
    xTaskCreate(vPixelTwoTask, "Pico Show 2", configMINIMAL_STACK_SIZE, NULL, NEOPIXEL_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
    gpio_put(CONTROL_PIN, false);// should not reach this one
}

PIXEL_COLOR* randomColor(void) {
    pixelColor.r = distr(gen);
    pixelColor.g = distr(gen);
    pixelColor.b = distr(gen);
    return &pixelColor;
}

PIXEL_COLOR RED = PIXEL_COLOR(255, 0, 0);
PIXEL_COLOR GREEN = PIXEL_COLOR(0, 255, 0);
PIXEL_COLOR BLUE = PIXEL_COLOR(0, 0, 255);
PIXEL_COLOR YELLOW = PIXEL_COLOR(255, 222, 33);
PIXEL_COLOR PUMPKIN(255, 45, 0);

PIXEL_COLOR CHRISTMAS_COLOURS[] ={RED, GREEN, BLUE, YELLOW, PUMPKIN};

PIXEL_COLOR* christmasColor() {
    return  &CHRISTMAS_COLOURS[christmas_distr(gen)];
}

uint16_t getType() {
    return std::stoi(PIXEL_TYPE);
}

void vPixelOneTask(void*) {
    LightShow lightShow(std::stoi(NUM_PIXELS), NEOPIXEL_PIN, getType());
    for(;;) {
        lightShow.glowing(&PUMPKIN, CYCLEDELAY, &level, adjust);
        vTaskDelay(PAUSE_TIME);
        lightShow.sparkle(christmasColor(), 30, DELAY_VAL);
        vTaskDelay(PAUSE_TIME);
        lightShow.colorWipe(randomColor);
        vTaskDelay(PAUSE_TIME);
        lightShow.theaterChase(christmasColor(), DELAY_VAL);
        vTaskDelay(PAUSE_TIME);
        lightShow.rainbow();
        vTaskDelay(PAUSE_TIME);
        lightShow.rainbowChase();
        vTaskDelay(PAUSE_TIME);
        lightShow.theaterChaseRainbow(DELAY_VAL);
        vTaskDelay(PAUSE_TIME);
    }
}

void vPixelTwoTask(void*) {
    LightShow lightShow(std::stoi(NUM_PIXELS2), NEOPIXEL2_PIN, NEO_RGB + NEO_KHZ800);
    for(;;) {
        lightShow.rainbow();
        vTaskDelay(PAUSE_TIME);
        lightShow.rainbowChase();
        vTaskDelay(PAUSE_TIME);
        lightShow.colorWipe(randomColor);
        vTaskDelay(PAUSE_TIME);
        lightShow.glowing(randomColor(),CYCLEDELAY, &level2, adjust2);
        vTaskDelay(PAUSE_TIME);
    }
}

// static functions
static uint8_t adjust (uint8_t value) {
    if (level == 0) return value ;
    return ((value * neopixels_gamma8(level)) >> 8) ;
}

static uint8_t adjust2 (uint8_t value) {
    if (level2 == 0) return value ;
    return ((value * neopixels_gamma8(level2)) >> 8) ;
}