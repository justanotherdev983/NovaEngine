#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "def.h"

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
    SDL_Texture* shotgun_texture;
    SDL_Texture* ascii_texture;

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


void move_player_forward(player_t* player, map_t map);
void move_player_backward(player_t* player, map_t map);
void rotate_player(player_t* player, float angle);

bool init_sdl(game_state_t* game);
void init_game(game_state_t* game);
bool load_resources(game_state_t* game);

void handle_events(game_state_t* game);
void cleanup(game_state_t* game);
void run_game(game_state_t* game);
void render_game(game_state_t* game);
void debug_info(game_state_t* game);