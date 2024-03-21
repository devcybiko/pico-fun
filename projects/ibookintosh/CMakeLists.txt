cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/home/projects/gtos -D__PICO__ -fdebug-prefix-map=${CMAKE_SOURCE_DIR}=.")
include(pico_sdk_import.cmake)
project(ibookintosh VERSION 1.0.0)

add_executable(ibookintosh
                main.c
               Tps65.c
               ../gtos/Template.c
               ../gtos/GCron.c
               ../gtos/GCronEntry.c
                ../gtos/GList.c
                ../gtos/GMap.c
                ../gtos/GObj.c
                ../gtos/GTimer.c
)

pico_sdk_init()

pico_enable_stdio_usb(ibookintosh 0)
pico_enable_stdio_uart(ibookintosh 1)
pico_add_extra_outputs(ibookintosh)

target_link_libraries(ibookintosh
                      pico_stdlib
                      hardware_gpio
                      hardware_i2c
                      hardware_spi
                      hardware_adc
                      hardware_uart)
