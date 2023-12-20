cmake_minimum_required(VERSION 3.12)

# Include the Pico SDK
include(../pico_sdk_import.cmake)

# Set the project name and version
project(blink_example)

# Initialize the Pico SDK
pico_sdk_init()

# Add the executable file (change "blink.c" to your source file name)
add_executable(blink blink.c)

# Link the executable with the Pico SDK libraries
target_link_libraries(blink pico_stdlib)

# Create a map/bin/hex/uf2 file etc.
pico_add_extra_outputs(blink)
