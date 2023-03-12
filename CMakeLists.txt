cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_DEOPTIMIZED_DEBUG 1)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/Users/timax/Development/pi_pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(example C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# dwm_pico_ws2812 library files
aux_source_directory(./dwm_pico_ws2812 dwm_pico_ws2812) #<-- Add library files

# Add executable. Default name is the project name
add_executable(example example.c ${dwm_pico_ws2812}) #<-- Add library (fles) to executable

# Generate pio header for dwm_pico_ws2812
set(dwm_pico_ws2812_DIR "${CMAKE_SOURCE_DIR}/dwm_pico_ws2812") #<-- This sets variable dwm_pico_ws2812_DIR needed below
pico_generate_pio_header(example ${dwm_pico_ws2812_DIR}/ws2812.pio OUTPUT_DIR ${dwm_pico_ws2812_DIR}/generated) #<-- Generate pio header

target_include_directories(example PRIVATE)

pico_set_program_name(example "example")
pico_set_program_version(example "1.0")

pico_enable_stdio_uart(example 1)
pico_enable_stdio_usb(example 0)

# Add the standard library to the build
target_link_libraries(example pico_stdlib hardware_pio) #<-- Add hardware_pio library

pico_add_extra_outputs(example)