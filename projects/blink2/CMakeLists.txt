cmake_minimum_required(VERSION 3.14)
include(pico_sdk_import.cmake)
project(blink2 VERSION 1.0.0)
add_executable(blink2
               blink2.c)

pico_sdk_init()

pico_enable_stdio_usb(blink2 1)
pico_enable_stdio_uart(blink2 1)
pico_add_extra_outputs(blink2)

target_link_libraries(blink2
                      pico_stdlib
                      hardware_gpio
                      hardware_i2c
                      hardware_spi
                      hardware_adc
                      hardware_uart)
