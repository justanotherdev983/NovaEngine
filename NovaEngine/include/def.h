#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>

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


typedef double f64;
typedef float f32;

typedef uint8_t i8;



typedef struct vec2i32 {
    i32 x;
    i32 y;
} vec2i32;

typedef int32_t i32s;

typedef struct vec2i32s {
    i32s x;
    i32s y;
} vec2i32s;

static inline vec2i32s vec2i32sadd(vec2i32s a, vec2i32s b) {
    return (vec2i32s){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2i32 vec2i32add(vec2i32 a, vec2i32 b) {
    return (vec2i32){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

typedef struct vec2f32 {
    f32 x;
    f32 y;
} vec2f32;

static inline vec2f32 vec2f32add(vec2f32 a, vec2f32 b) {
    return (vec2f32){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2f32 vec2f32sub(vec2f32 a, vec2f32 b) {
    return (vec2f32){
        .x = a.x - b.x,
        .y = a.y - b.y
    };
}

typedef struct vec2i64 {
    i64 x;
    i64 y;
} vec2i64;

static inline vec2i64 vec2i64add(vec2i64 a, vec2i64 b) {
    return (vec2i64){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

typedef struct vec2f64 {
    f32 x;
    f32 y;
} vec2f64;

static inline vec2f64 vec2f64add(vec2f64 a, vec2f64 b) {
    return (vec2f64){
        .x = a.x + b.x,
        .y = a.y + b.y
    };
}

static inline vec2f32 vec2f32scale(vec2f32 v, f32 scale) {
    return (vec2f32){
        .x = v.x * scale,
        .y = v.y * scale
    };
}

static inline f32 vec2f32length(vec2f32 v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

static inline vec2f32 vec2f32normalize(vec2f32 v) {
    f32 len = vec2f32length(v);
    if (len == 0) return (vec2f32){0, 0};
    return vec2f32scale(v, 1.0f / len);
}

// game structs

typedef struct {
    vec2f32 side_dist;
    vec2f32 delta_dist;
    int step_x;
    int step_y;
} dda_params_t;

typedef struct {
    bool hit;
    int side;
    vec2f32 map_pos;
    float perp_wall_dist;
} ray_collision_t;

typedef struct {
    int line_height;
    int draw_start;
    int draw_end;
} wall_params_t;



typedef struct map {
    int* data;
    i32 width;
    i32 height;
} map_t;

typedef struct player {
    vec2f32 position;
    vec2f32 direction;
    vec2f32 plane;
} player_t;

typedef struct ray {
    vec2f32 position;
    vec2f32 direction;
} ray_t;

typedef struct camera {
    vec2f32 position;
    vec2f32 direction;
    vec2f32 plane;
} camera_t;


typedef struct game_state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Surface* shotgun_surface;
    SDL_Surface* ascii_surface;
    SDL_Texture* shotgun_texture;
    SDL_Texture* ascii_texture;
    char* ascii_art;
    SDL_Color cur_color;

    struct {
        map_t map;
        player_t player;
        camera_t camera;
    } world;
    
    struct {
        SDL_Window* window;
        SDL_Renderer* renderer;
    } world_2d;

    int image_width;
    int image_height;
    bool is_running;

} game_state_t;