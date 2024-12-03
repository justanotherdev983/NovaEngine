#pragma once

#include <stdbool.h>

#include "game.h"
#include "def.h"
#include "ascii.h"



ray_t init_ray(vec2f32 position, vec2f32 direction);

camera_t init_camera(vec2f32 position, vec2f32 direction, vec2f32 plane);
player_t init_player(vec2f32 position, vec2f32 direction, vec2f32 plane);

map_t init_map(void);

bool has_collided(float x, float y, map_t map);

void render_2d_map(vec2f32 player_pos, SDL_Renderer* renderer);


ray_t calculate_ray(camera_t camera, int x, int screen_width);
dda_params_t calculate_dda_params(ray_t ray, vec2f32 map_pos);


ray_collision_t perform_dda(ray_t ray, map_t map, dda_params_t params);


wall_params_t calculate_wall_params(ray_collision_t collision, int screen_height);

void cast_ray(game_state_t* game, player_t player, map_t map, SDL_Renderer* renderer);
