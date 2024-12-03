#include "ascii.h"

// Returns unfree'd char* 
char* generate_random_ascii_art(int len) {
    // Stricter length validation
    if (len <= 0) {
        ERROR_MSG("Invalid length provided");
        return NULL;
    }

    // Validate ASCII_CHARS exists and has content
    int num_chars = strlen(ASCII_CHARS);
    if (num_chars == 0) {
        ERROR_MSG("No ASCII characters available");
        return NULL;
    }

    // Allocate memory
    char* ascii_art = (char*)calloc(len + 1, sizeof(char));
    if (!ascii_art) {
        ERROR_MSG("Failed to allocate memory for ascii_art");
        return NULL;
    }

    // Generate random ASCII art
    for (int i = 0; i < len; ++i) {
        ascii_art[i] = ASCII_CHARS[rand() % num_chars];
    }
    ascii_art[len] = '\0';  // Ensure null-termination
    LOG_MSG("Generated ASCII art: %s", ascii_art);
    return ascii_art;
}



SDL_Color determine_ascii_brightness(ray_collision_t collision) {
    SDL_Color color = {
        collision.side == 1 ? 200 : 255,  // R
        collision.side == 1 ? 200 : 0,    // G
        collision.side == 1 ? 200 : 0,    // B
        255                               // A
    };
    
    // Potential future enhancements:
    // 1. Factor in distance to create depth shading
    // float distance_factor = 1.0f - fminf(collision.perp_wall_dist / MAX_RENDER_DISTANCE, 1.0f);
    // color.r *= distance_factor;
    // color.g *= distance_factor;
    // color.b *= distance_factor;
    
    return color;
}

void draw_ascii_wall_slice(game_state_t* game, SDL_Renderer* renderer, int x, wall_params_t wall, ray_collision_t collision) {
    // Safety check: Ensure the line height is valid and the ASCII art is enabled
    if (wall.line_height <= 0 || !game->ascii_art) {
        return;
    }

    // Determine the color for the ASCII slice based on the collision
    SDL_Color slice_color = determine_ascii_brightness(collision);

    // Get the ASCII character to display for this wall slice (using game->ascii_art)
    char slice_char = game->ascii_art[x]; // Get the character at this column

    // The width and height of a single character slice in the ASCII texture
    int char_width = 8;  // Width of each character slice in pixels (adjust as needed)
    int char_height = 16; // Height of each character slice in pixels (adjust as needed)

    // Get the ASCII value of the character
    int ascii_value = (int) slice_char; 

    // Calculate texture coordinates assuming a 16x16 grid of ASCII characters in the texture
    int texture_x = (ascii_value % 16) * char_width;  // Modulo for columns
    int texture_y = (ascii_value / 16) * char_height; // Integer division for rows


    // Set up the destination rectangle for the slice
    SDL_Rect dstrect = {
        x,                    // X position on the screen
        wall.draw_start,       // Starting Y position of the wall slice
        1,                     // Width of the slice (1 pixel wide for each column)
        wall.line_height       // Height of the slice (the height of the wall slice)
    };

    // Set up the source rectangle to extract the correct ASCII character from the texture
    SDL_Rect srcrect = {
        texture_x,            // X position in the ASCII texture for the character
        texture_y,            // Y position in the ASCII texture for the character
        char_width,           // Width of one character slice
        char_height           // Height of one character slice
    };

    // Render the ASCII character slice from the pre-rendered ASCII texture
    SDL_SetTextureColorMod(game->ascii_texture, slice_color.r, slice_color.g, slice_color.b);
    SDL_RenderCopy(renderer, game->ascii_texture, &srcrect, &dstrect);
}


SDL_Texture* generate_ascii_SDL_texture(game_state_t* game, SDL_Renderer* renderer, TTF_Font* font, SDL_Surface* input_surface) {
    if (!input_surface) {
        ERROR_MSG("Invalid surface provided");
        return NULL;
    }

    if (SDL_MUSTLOCK(input_surface)) {
        if (SDL_LockSurface(input_surface) != 0) {
            ERROR_MSG("Failed to lock surface: %s", SDL_GetError());
            return NULL;
        }
    }

    SDL_Surface* formatted_surface = SDL_ConvertSurfaceFormat(input_surface, SDL_PIXELFORMAT_ARGB8888, 0);
    if (!formatted_surface) {
        ERROR_MSG("Failed to convert surface format: %s", SDL_GetError());
        if (SDL_MUSTLOCK(input_surface)) {
            SDL_UnlockSurface(input_surface);
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
        if (SDL_MUSTLOCK(input_surface)) {
            SDL_UnlockSurface(input_surface);
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
    for (int y = 0; y < height; y += SCALE) { // Step by SCALE for better alignment
        for (int x = 0; x < width; x += SCALE) {
            Uint32 pixel = pixels[y * pitch + x];
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, formatted_surface->format, &r, &g, &b, &a);

            if (a > 128) { // Only render ASCII characters on active pixels
                char ascii_char[2] = {game->ascii_art[y * formatted_surface->w + x], '\0'};

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
    if (SDL_MUSTLOCK(input_surface)) {
        SDL_UnlockSurface(input_surface);
    }
    return ascii_texture;
}