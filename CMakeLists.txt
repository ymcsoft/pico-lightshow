cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)
include(pico_sdk_import.cmake)
# Pull in FreeRTOS
include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(pico_lightshow C CXX ASM)

if (DEFINED ENV{NUM_PIXELS} AND (NOT NUM_PIXELS))
    set(NUM_PIXELS $ENV{NUM_PIXELS})
    message("Using NUM_PIXELS from environment ('${NUM_PIXELS}')")
endif()

if (DEFINED ENV{NUM_PIXELS2} AND (NOT NUM_PIXELS2))
    set(NUM_PIXELS2 $ENV{NUM_PIXELS2})
    message("Using NUM_PIXELS2 from environment ('${NUM_PIXELS2}')")
endif()

if (DEFINED ENV{PIXEL_TYPE} AND (NOT PIXEL_TYPE))
    set(PIXEL_TYPE $ENV{PIXEL_TYPE})
    message("Using PIXEL_TYPE from environment ('${PIXEL_TYPE}')")
endif()

if (DEFINED ENV{PAUSE} AND (NOT PAUSE))
    set(PAUSE $ENV{PAUSE})
    message("Using PAUSE from the environment ('${PAUSE}')")
endif()

pico_sdk_init()

add_subdirectory(pico_neopixels)
include_directories(include)
set(SOURCES src/main.cpp lib/LightShow.cpp lib/br_iterator.h lib/range.h)
add_executable(pico_lightshow ${SOURCES})
target_compile_definitions(pico_lightshow PRIVATE
        NUM_PIXELS=\"${NUM_PIXELS}\"
        NUM_PIXELS2=\"${NUM_PIXELS2}\"
        PIXEL_TYPE=\"${PIXEL_TYPE}\"
        PAUSE=\"${PAUSE}\"
        )

pico_enable_stdio_usb(pico_lightshow 1)
pico_enable_stdio_uart(pico_lightshow 0)

target_link_libraries(pico_lightshow pico_stdlib pico_neopixel FreeRTOS-Kernel FreeRTOS-Kernel-Heap4)

# create map/bin/hex file etc.
pico_add_extra_outputs(pico_lightshow)
