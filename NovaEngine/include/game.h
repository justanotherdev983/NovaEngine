#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "def.h"
#include "raycast.h"
#include "ascii.h"

void move_player_forward(player_t* player, map_t map);
void move_player_backward(player_t* player, map_t map);
void rotate_player(player_t* player, float angle);

bool init_sdl(game_state_t* game);
void init_game(game_state_t* game);

void handle_events(game_state_t* game);
void cleanup(game_state_t* game);
void run_game(game_state_t* game);
void render_game(game_state_t* game);
void debug_info(game_state_t* game);