#include <random>
#include "LightShow.h"
// Which pin on the Pico is connected to the NeoPixels?
#define NEOPIXEL_PIN        0 // The first port using GP0
#define NEOPIXEL2_PIN       2 // The second port using GP2
#define DELAY_VAL 100

PIXEL_COLOR pixelColor;
std::uniform_int_distribution<> distr(0, 255);
std::random_device dev;
std::mt19937 gen(dev());

const uint32_t PAUSE_TIME = 5000;

PIXEL_COLOR* randomColor(void);
uint16_t getType();

void vPixelOneTask(void*);
void vPixelTwoTask(void*);

int main () {
    stdio_init_all();
    TaskHandle_t task;
    xTaskCreate(vPixelOneTask, "Pico Show 1", configMINIMAL_STACK_SIZE, NULL, NEOPIXEL_TASK_PRIORITY, &task);
#if NO_SYS && configUSE_CORE_AFFINITY && configNUM_CORES > 1
    // we must bind the main task to one core (well at least while the init is called)
    // (note we only do this in NO_SYS mode, because cyw43_arch_freertos
    // takes care of it otherwise)
    vTaskCoreAffinitySet(task, 1);
#endif
    xTaskCreate(vPixelTwoTask, "Pico Show 2", configMINIMAL_STACK_SIZE, NULL, NEOPIXEL_TASK_PRIORITY, NULL);
    vTaskStartScheduler();
}

PIXEL_COLOR* randomColor(void) {
    pixelColor.r = distr(gen);
    pixelColor.g = distr(gen);
    pixelColor.b = distr(gen);
    return &pixelColor;
}

uint16_t getType() {
    return std::stoi(PIXEL_TYPE);
}

void vPixelOneTask(void*) {
    PIXEL_COLOR pumpkin(255, 45, 0);
    LightShow lightShow(std::stoi(NUM_PIXELS), NEOPIXEL_PIN, getType());
    for(;;) {
        lightShow.glowing(&pumpkin);
        vTaskDelay(PAUSE_TIME);
        lightShow.sparkle(&pumpkin, 20, 5);
        vTaskDelay(PAUSE_TIME);
        lightShow.colorWipe(randomColor);
        vTaskDelay(PAUSE_TIME);
        lightShow.theaterChase(&pumpkin, DELAY_VAL);
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
        lightShow.sparkle(randomColor(), 10, 5);
        vTaskDelay(PAUSE_TIME);
        lightShow.rainbow();
        vTaskDelay(PAUSE_TIME);
        lightShow.colorWipe(randomColor);
        vTaskDelay(PAUSE_TIME);
        lightShow.glowing(randomColor());
        vTaskDelay(PAUSE_TIME);
    }
}