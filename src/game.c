#include "game.h"

bool init_sdl(game_state_t* game) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return false;
    }


    game->window = SDL_CreateWindow("Nova Engine: Delirious Adventure",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!game->window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!game->renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return false;
    }

    game->world_2d.window = SDL_CreateWindow("2D Map",
        SDL_WINDOWPOS_CENTERED / 2, SDL_WINDOWPOS_CENTERED / 2,
        400, 400, 0);
    game->world_2d.renderer = SDL_CreateRenderer(game->world_2d.window, -1, SDL_RENDERER_ACCELERATED);

    // Enable alpha blending
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_BLEND);
    return true;
}

bool load_resources(game_state_t* game) {
    game->font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 8);
    if (!game->font) {
        ERROR_MSG("TTF_OpenFont Error: %s", TTF_GetError());
        return false;
    }

    game->shotgun_surface = IMG_Load("../assets/shotgun");
    if (!game->shotgun_surface) {
        ERROR_MSG("IMG_Load Error: %s", IMG_GetError());
        return false;
    }

    LOG_MSG("Surface format: bpp=%d, format=%d",
            game->shotgun_surface->format->BitsPerPixel,
            game->shotgun_surface->format->format);

    game->image_width = game->shotgun_surface->w;
    game->image_height = game->shotgun_surface->h;

    LOG_MSG("Loaded image dimensions: %dx%d", game->image_width, game->image_height);

    // Create shotgun texture
    game->shotgun_texture = SDL_CreateTextureFromSurface(game->renderer, game->shotgun_surface);
    if (!game->shotgun_texture) {
        ERROR_MSG("Failed to create shotgun texture: %s", SDL_GetError());
        SDL_FreeSurface(game->shotgun_surface); // Free surface in case of error
        return false;
    }

    // Create ASCII texture
    game->ascii_texture = generate_ascii_SDL_texture(game->renderer, game->font, game->shotgun_surface);
    if (!game->ascii_texture) {
        ERROR_MSG("Failed to create ASCII texture: %s", SDL_GetError());
        SDL_FreeSurface(game->shotgun_surface); // Free surface in case of error
        SDL_DestroyTexture(game->shotgun_texture);
        return false;
    }

    SDL_FreeSurface(game->shotgun_surface);
    return true;
}

void move_player_forward(player_t* player, map_t map) {
    vec2f32 new_position = vec2f32add(player->position, vec2f32scale(player->direction, SPEED));
    if (!has_collided(new_position.x, new_position.y, map)) {
        player->position = new_position;
    }
}

void move_player_backward(player_t* player, map_t map) {
    vec2f32 new_position = vec2f32sub(player->position, vec2f32scale(player->direction, SPEED));
    if (!has_collided(new_position.x, new_position.y, map)) {
        player->position = new_position;
    }
}


void rotate_player(player_t* player, float angle) {
    // Rotation matrix calculation
    float cos_angle = cosf(angle);
    float sin_angle = sinf(angle);

    // Rotate direction vector
    vec2f32 new_direction = {
        player->direction.x * cos_angle - player->direction.y * sin_angle,
        player->direction.x * sin_angle + player->direction.y * cos_angle
    };

    // Rotate camera plane
    vec2f32 new_plane = {
        player->plane.x * cos_angle - player->plane.y * sin_angle,
        player->plane.x * sin_angle + player->plane.y * cos_angle
    };

    player->direction = new_direction;
    player->plane = new_plane;
}


void handle_events(game_state_t* game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game->is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        game->is_running = false;
                        break;
                    case SDLK_w:
                        move_player_forward(&game->world.player, game->world.map);
                        LOG_MSG("Player position: %f, %f", game->world.player.position.x, game->world.player.position.y);
                        break;
                    case SDLK_s:
                        move_player_backward(&game->world.player, game->world.map);
                        LOG_MSG("Player position: %f, %f", game->world.player.position.x, game->world.player.position.y);
                        break;
                    case SDLK_a:
                        rotate_player(&game->world.player, 0.1f);
                        break;
                    case SDLK_d:
                        rotate_player(&game->world.player, -0.1f);
                        break;
                }
                break;
        }
    }
}


void render_game(game_state_t* game) {
    

    //SDL_SetRenderDrawColor(game->renderer, 64, 64, 128, 255);
    SDL_Rect ceiling = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    SDL_RenderFillRect(game->renderer, &ceiling);


    SDL_SetRenderDrawColor(game->renderer, 96, 96, 96, 255);
    SDL_Rect floor = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2};
    SDL_RenderFillRect(game->renderer, &floor);


    cast_ray(game->world.player, game->world.map, game->renderer);
    
}


void render(game_state_t* game) {
    SDL_SetRenderDrawColor(game->renderer, 50, 3, 252, 255);
    SDL_RenderClear(game->renderer);

    render_game(game);
    render_2d_map(game->world.player.position, game->world_2d.renderer);
    SDL_RenderPresent(game->world_2d.renderer);

    int x = (WINDOW_WIDTH - game->image_width) / 2;
    int y = (WINDOW_HEIGHT - game->image_height) / 2;
    SDL_Rect dest = {
        x, 
        y, 
        game->image_width * SCALE, 
        game->image_height * SCALE,
    };

    SDL_RenderCopy(game->renderer, game->shotgun_texture, NULL, &dest);
    SDL_RenderCopy(game->renderer, game->ascii_texture, NULL, &dest);

    

    SDL_RenderPresent(game->renderer);
}

void cleanup(game_state_t* game) {
    if (game->ascii_texture) SDL_DestroyTexture(game->ascii_texture);
    if (game->shotgun_texture) SDL_DestroyTexture(game->shotgun_texture);
    if (game->font) TTF_CloseFont(game->font);
    if (game->renderer) SDL_DestroyRenderer(game->renderer);
    if (game->window) SDL_DestroyWindow(game->window);
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


void run_game(game_state_t* game) {
    game->is_running = true;
    init_game(game);
    while (game->is_running) {
        handle_events(game);
        render(game);
        SDL_Delay(16);
    }
}

void init_game(game_state_t* game) {
    
    vec2f32 initial_position = {1.5f, 1.5f}; // Starting in an open space
    vec2f32 initial_direction = {-1.0f, 0.0f}; // Facing left
    vec2f32 initial_plane = {0.0f, 0.66f}; // Camera plane
    game->world.player = init_player(initial_position, initial_direction, initial_plane);
    game->world.map = init_map();
    //game->world.player = init_player(game->world.player.position, game->world.player.direction, game->world.player.plane);
    game->world.camera = init_camera(game->world.player.position, game->world.player.direction, game->world.player.plane);
}

void debug_info(game_state_t* game) {

    SDL_RendererInfo info;
    SDL_GetRendererInfo(game->renderer, &info);
    LOG_MSG("Rederer name: %s", info.name);
    LOG_MSG("Renderer flags: %u\n", info.flags);
    LOG_MSG("Number of texture formats: %u\n", info.num_texture_formats);
    for (Uint32 i = 0; i < info.num_texture_formats; i++) {
        LOG_MSG("  Format %u: %u", i, info.texture_formats[i]);
    }
}
