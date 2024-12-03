#pragma once

#include <stdint.h>
#include <stdio.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define ASCII_CHARS " .:-=+*#%@"
#define SCALE 5


#define LOG_MSG(fmt, ...) printf("[LOG]: " fmt "\n", ##__VA_ARGS__)
#define ERROR_MSG(fmt, ...) fprintf(stderr, "[ERROR]: " fmt "\n", ##__VA_ARGS__)

#define DEG_TO_RAD M_PI / 180.0f
#define SPEED 0.5f
#define MAX_VELOCITY 0.5f

typedef uint64_t i64;
typedef uint32_t i32;
typedef uint8_t i8;

typedef double f64;
typedef float f32;