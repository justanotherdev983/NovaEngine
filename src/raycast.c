#include "raycast.h"

ray_t init_ray(vec2f32 position, vec2f32 direction) {
    ray_t ray = {
        .position = position,
        .direction = direction
    };
    return ray;
}

camera_t init_camera(vec2f32 position, vec2f32 direction, vec2f32 plane) {
    camera_t camera = {
        .position = position,
        .direction = direction,
        .plane = plane
    };
    return camera;
}

player_t init_player(vec2f32 position, vec2f32 direction, vec2f32 plane) {
    player_t player = {
        .position = position,
        .direction = direction,
        .plane = plane,
    };
    return player;
}

map_t init_map(void) {
    static int map_data[100] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    
    map_t map = {
        .data = map_data,
        .width = 10,
        .height = 10
    };
    
    return map;
}

bool has_collided(float x, float y, map_t map) {
    i32 map_x = (i32)x;
    i32 map_y = (i32)y;
    if (map_x >= map.width || map_y >= map.height) {
        return true;
    }
    return map.data[map_x + map_y * map.width] == 1;
}

void render_2d_map(vec2f32 player_pos, SDL_Renderer* renderer) {
    const int CELL_SIZE = 32;
    const int MAP_WIDTH = 10;
    const int MAP_HEIGHT = 10;

    map_t map = init_map();

    // Calculate offset to center the map
    int offset_x = (400 - (MAP_WIDTH * CELL_SIZE)) / 2;
    int offset_y = (400 - (MAP_HEIGHT * CELL_SIZE)) / 2;


    // Draw map cells
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            SDL_Rect cell = {
                offset_x + (x * CELL_SIZE),
                offset_y + (y * CELL_SIZE),
                CELL_SIZE,
                CELL_SIZE
            };

            if (has_collided(x, y, map)) {
                // Draw walls
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &cell);
            } else {
                // Draw floor
                SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
                SDL_RenderFillRect(renderer, &cell);
            }
        }
    }

    // Draw player position
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect player = {
        offset_x + ((int)player_pos.x * CELL_SIZE),
        offset_y + ((int)player_pos.y * CELL_SIZE),
        CELL_SIZE / 4,
        CELL_SIZE / 4
    };
    SDL_RenderFillRect(renderer, &player);
}

// Calculate ray direction based on screen x-coordinate
ray_t calculate_ray(camera_t camera, int x, int screen_width) {
    float camera_x = 2.0f * x / (float)screen_width - 1.0f;
    vec2f32 ray_dir = {
        camera.direction.x + camera.plane.x * camera_x,
        camera.direction.y + camera.plane.y * camera_x
    };
    return init_ray(camera.position, ray_dir);
}

dda_params_t calculate_dda_params(ray_t ray, vec2f32 map_pos) {
    dda_params_t params;
    
    // Calculate delta distances
    params.delta_dist.x = fabsf(ray.direction.x) < 1e-20 ? 1e30 : fabsf(1.0f / ray.direction.x);
    params.delta_dist.y = fabsf(ray.direction.y) < 1e-20 ? 1e30 : fabsf(1.0f / ray.direction.y);

    // Calculate step and initial side_dist
    if (ray.direction.x < 0) {
        params.step_x = -1;
        params.side_dist.x = (ray.position.x - map_pos.x) * params.delta_dist.x;
    } else {
        params.step_x = 1;
        params.side_dist.x = (map_pos.x + 1.0f - ray.position.x) * params.delta_dist.x;
    }

    if (ray.direction.y < 0) {
        params.step_y = -1;
        params.side_dist.y = (ray.position.y - map_pos.y) * params.delta_dist.y;
    } else {
        params.step_y = 1;
        params.side_dist.y = (map_pos.y + 1.0f - ray.position.y) * params.delta_dist.y;
    }

    return params;
}

// Perform DDA algorithm to find wall collision
ray_collision_t perform_dda(ray_t ray, map_t map, dda_params_t params) {
    ray_collision_t collision = {0};
    collision.map_pos.x = (int)ray.position.x;
    collision.map_pos.y = (int)ray.position.y;

    while (!collision.hit) {
        if (params.side_dist.x < params.side_dist.y) {
            params.side_dist.x += params.delta_dist.x;
            collision.map_pos.x += params.step_x;
            collision.side = 0;
        } else {
            params.side_dist.y += params.delta_dist.y;
            collision.map_pos.y += params.step_y;
            collision.side = 1;
        }

        if (has_collided(collision.map_pos.x, collision.map_pos.y, map)) {
            collision.hit = true;
            collision.perp_wall_dist = collision.side == 0 
                ? params.side_dist.x - params.delta_dist.x
                : params.side_dist.y - params.delta_dist.y;
        }
    }

    return collision;
}


wall_params_t calculate_wall_params(ray_collision_t collision, int screen_height) {
    wall_params_t params;
    
    params.line_height = (int)(screen_height / collision.perp_wall_dist);
    
    params.draw_start = -params.line_height / 2 + screen_height / 2;
    if (params.draw_start < 0) params.draw_start = 0;
    
    params.draw_end = params.line_height / 2 + screen_height / 2;
    if (params.draw_end >= screen_height) params.draw_end = screen_height - 1;
    
    return params;
}

void cast_ray(player_t player, map_t map, SDL_Renderer* renderer) {
    camera_t camera = {
        .position = player.position,
        .direction = player.direction,
        .plane = player.plane
    };

    for (int x = 0; x < WINDOW_WIDTH; x++) {
        // Calculate ray for this column
        ray_t ray = calculate_ray(camera, x, WINDOW_WIDTH);
        
        // Calculate DDA parameters
        dda_params_t dda_params = calculate_dda_params(ray, camera.position);
        
        // Perform DDA to find wall collision
        ray_collision_t collision = perform_dda(ray, map, dda_params);
        
        // Calculate wall rendering parameters
        wall_params_t wall = calculate_wall_params(collision, WINDOW_HEIGHT);
        
        // Draw the wall slice
        draw_ascii_wall_slice(renderer, x, wall, collision);
    }
}
