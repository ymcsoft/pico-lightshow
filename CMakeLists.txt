cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)
include(pico_sdk_import.cmake)

project(pico_lightshow C CXX ASM)

pico_sdk_init()

add_executable(pico_lightshow main.cpp LightShow.cpp LightShow.h br_iterator.h)
add_subdirectory(pico_neopixels)

pico_enable_stdio_usb(pico_lightshow 1)
pico_enable_stdio_uart(pico_lightshow 0)

target_link_libraries(pico_lightshow pico_stdlib pico_neopixel)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_lightshow)
