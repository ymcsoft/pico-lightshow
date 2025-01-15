# Pico Christmas Light Show

This project is a sample Raspberry Pi Pico project that uses the Adafruit Neopixel library to create various light show effects. The project demonstrates how to control NeoPixel LEDs using the Raspberry Pi Pico and FreeRTOS.

## Features

- Glowing effect
- Sparkle effect
- Color wipe effect
- Theater chase effect
- Rainbow effect
- Rainbow chase effect

![Light Show Demo](lightshow.gif)

## Prerequisites

- Raspberry Pi Pico
- NeoPixel LEDs
- CMake (version 3.13 or higher)
- Pico SDK
- FreeRTOS Kernel
- GCC (GNU Compiler Collection)
- Python 3 (for Pico SDK setup)
- Git (for cloning repositories)

### Configuring toolchain for RS2350 RISC-V architecture

To build the project, you need to configure the toolchain for the RS2350 RISC-V architecture. Follow these steps to configure the toolchain:
* Download the RISC-V toolchain from [here](https://embecosm.com/downloads/tool-chain-downloads/#risc-v-embedded-top-of-tree-compilers).
* Extract the downloaded directory to a directory on your system.
* Add the toolchain to your system's PATH environment variable or set PICO_TOOLCHAIN_PATH environment variable since there might be multiple toolchains configured in the system. You can do this by adding the following line to your shell configuration file (e.g., ~/.bashrc, ~/.zshrc, etc.):
  ```sh
  export PICO_TOOLCHAIN_PATH=/path/to/riscv-toolchain
  ```

## Building the Project

To build the project, follow these steps:

1. **Set up the Pico SDK:**

   Follow the instructions to set up the Pico SDK on your system. You can find the setup guide [here](https://github.com/raspberrypi/pico-sdk).

2. **Clone the Repository:**

   ```sh
   git clone https://github.com/yourusername/pico-lightshow.git
   cd pico-lightshow
    ```
3. Set Environment Variables:  Set the following environment variables according to your setup:  
   ```
   export PICO_SDK_PATH=/path/to/pico-sdk
   export FREERTOS_KERNEL_PATH=/path/to/FreeRTOS-Kernel
   export NUM_PIXELS=30# Number of NeoPixel LEDs
   export NUM_PIXELS2=30# Number of NeoPixel LEDs
   export PIXEL_TYPE=NEO_GRB + NEO_KHZ800
   export DELAY=100# Delay in milliseconds
   export PAUSE=500# Pause in milliseconds`
    ```
4. Create Build Directory:  
   ```sh
   mkdir build
   cd build
    ```
5. Run CMake:  
    ```sh
    cmake ..
     ```
6. Build the Project:  
    ```sh
   make
    ```
7. Upload to Raspberry Pi Pico:  

After building, you will have a .uf2 file in the build directory. Press and hold the BOOTSEL button on your Pico, connect it to your computer, and copy the .uf2 file to the Pico's storage.  

## Usage
Once the code is uploaded to the Raspberry Pi Pico, it will start running the light show effects on the connected NeoPixel LEDs.  
## License
This project is licensed under the MIT License. 
## Developed By
This project was developed by Yuri Moiseyenko, © YMC Software Inc. All rights reserved.