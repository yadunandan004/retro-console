cmake_minimum_required(VERSION 3.16)
project(chip8_emulator)

# Use C++20 for modern features
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable debug symbols for better debugging experience
set(CMAKE_BUILD_TYPE Debug)

# Find SDL2 using pkg-config (works well on macOS with Homebrew)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Add our source files
set(SOURCES
    src/main.cpp
)

# Create the executable
add_executable(chip8_emulator ${SOURCES})


# Link SDL2 libraries
target_link_libraries(chip8_emulator ${SDL2_LIBRARIES})

# Add include directories for SDL2
target_include_directories(chip8_emulator PRIVATE ${SDL2_INCLUDE_DIRS})

# Add compiler flags for SDL2
target_compile_options(chip8_emulator PRIVATE ${SDL2_CFLAGS_OTHER})

# Add library directories for SDL2
target_link_directories(chip8_emulator PRIVATE ${SDL2_LIBRARY_DIRS})

# Enable compiler warnings to catch potential issues
target_compile_options(chip8_emulator PRIVATE
    -Wall -Wextra -Wpedantic
)
