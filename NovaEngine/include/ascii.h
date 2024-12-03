#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#include "def.h"
#include "raycast.h"

char* generate_random_ascii_art(int len);
void draw_ascii_wall_slice(game_state_t* game, SDL_Renderer* renderer, int x, wall_params_t wall, ray_collision_t collision);
SDL_Texture* generate_ascii_SDL_texture(game_state_t* game, SDL_Renderer* renderer, TTF_Font* font, SDL_Surface* input_surface);