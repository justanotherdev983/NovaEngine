#include "game.h"
#include "raycast.h"
#include "def.h"

char* generate_random_ascii_art(int len) {
    char* ascii_art = calloc(len + 1, sizeof(char));
    if (!ascii_art) {
        ERROR_MSG("Failed to allocate memory for ascii_art");
        return NULL;
    }
    int num_chars = strlen(ASCII_CHARS);
    for (int i = 0; i < len; ++i) {
        ascii_art[i] = ASCII_CHARS[rand() % num_chars];
    }
    ascii_art[len - 1] = '\0';
    return ascii_art;
}

SDL_Texture* generate_ascii_texture(SDL_Renderer* renderer, TTF_Font* font, SDL_Surface* shotgun_surface) {
    if (!shotgun_surface) {
        ERROR_MSG("Invalid surface provided");
        return NULL;
    }

    if (SDL_MUSTLOCK(shotgun_surface)) {
        if (SDL_LockSurface(shotgun_surface) != 0) {
            ERROR_MSG("Failed to lock surface: %s", SDL_GetError());
            return NULL;
        }
    }

    SDL_Surface* formatted_surface = SDL_ConvertSurfaceFormat(shotgun_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    if (!formatted_surface) {
        ERROR_MSG("Failed to convert surface format: %s", SDL_GetError());
        if (SDL_MUSTLOCK(shotgun_surface)) {
            SDL_UnlockSurface(shotgun_surface);
        }
        return NULL;
    }

    SDL_Texture* ascii_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, 
                                                   SDL_TEXTUREACCESS_TARGET, 
                                                   formatted_surface->w, 
                                                   formatted_surface->h);
    if (!ascii_texture) {
        ERROR_MSG("Failed to create ASCII texture: %s", SDL_GetError());
        SDL_FreeSurface(formatted_surface);
        if (SDL_MUSTLOCK(shotgun_surface)) {
            SDL_UnlockSurface(shotgun_surface);
        }
        return NULL;
    }

    SDL_SetTextureBlendMode(ascii_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, ascii_texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    Uint32* pixels = (Uint32*)formatted_surface->pixels;
    int width = formatted_surface->w;
    int height = formatted_surface->h;
    int pitch = formatted_surface->pitch / 4; // to u_int32_t

    SDL_Color textColor = {255, 255, 255, 255};
    char* ascii_art = generate_random_ascii_art(width * height);

    for (int y = 0; y < height; y += SCALE) { // Step by SCALE for better alignment
        for (int x = 0; x < width; x += SCALE) {
            Uint32 pixel = pixels[y * pitch + x];
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, formatted_surface->format, &r, &g, &b, &a);

            if (a > 0) { // Only render ASCII characters on active pixels
                char ascii_char[2] = {ascii_art[y * pitch + x]};

                SDL_Surface* text_surface = TTF_RenderText_Blended(font, ascii_char, textColor);

                if (text_surface) {
                    SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
                    if (text_texture) {
                        SDL_Rect text_rect = {x, y, SCALE, SCALE};
                        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
                        SDL_DestroyTexture(text_texture);
                    }
                    SDL_FreeSurface(text_surface);
                }
            }
        }
    }

    SDL_SetRenderTarget(renderer, NULL);
    SDL_FreeSurface(formatted_surface);
    if (SDL_MUSTLOCK(shotgun_surface)) {
        SDL_UnlockSurface(shotgun_surface);
    }
    return ascii_texture;
}

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
    game->ascii_texture = generate_ascii_texture(game->renderer, game->font, game->shotgun_surface);
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
