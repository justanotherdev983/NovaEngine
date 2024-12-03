# Minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Project name and language
project(nova LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g -fsanitize=address")

# Include FindPkgConfig module
include(FindPkgConfig)

# Find SDL2
pkg_check_modules(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

# Find SDL2_ttf
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
include_directories(${SDL2_TTF_INCLUDE_DIRS})
link_directories(${SDL2_TTF_LIBRARY_DIRS})

# Find SDL2_image
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
link_directories(${SDL2_IMAGE_LIBRARY_DIRS})

# Add project include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.c
    src/core/engine.c
    src/core/world.c
    src/input/input_handler.c
    src/physics/collision.c
    src/render/ascii_render.c
    src/render/sdl_render.c
    src/render/raycast.c
    src/util/math.c
    src/util/error.c
)

# Add executable
add_executable(nova ${SOURCES})

# Link libraries (SDL2, SDL2_ttf, SDL2_image, and math library)
target_link_libraries(nova ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} m)

# Set the output directory for the compiled binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# Find clang-format
find_program(CLANG_FORMAT_EXE NAMES clang-format)

# Include header files in the formatting process
file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h)
list(APPEND SOURCES ${HEADER_FILES})

# Define a custom target for formatting
if(CLANG_FORMAT_EXE)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT_EXE} -i ${SOURCES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang-format on source and header files"
    )
endif()

# Configure clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
    set(CLANG_TIDY_CHECKS "-*,clang-analyzer-*,modernize-*")
    set_target_properties(nova PROPERTIES C_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()
