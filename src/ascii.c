#include "ascii.h"

char* generate_random_ascii_art(int len) {
    char* ascii_art = (char*)calloc(len + 1, sizeof(char));
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

void draw_ascii_wall_slice(SDL_Renderer* renderer, int x, wall_params_t wall, ray_collision_t collision) {
    SDL_SetRenderDrawColor(renderer,
                collision.side == 1 ? 200 : 255,  // Different brightness for sides
                collision.side == 1 ? 200 : 0,
                collision.side == 1 ? 200 : 0,
                255);
            SDL_RenderDrawLine(renderer, x, wall.draw_start, x, wall.draw_end);
}

SDL_Texture* generate_ascii_SDL_texture(SDL_Renderer* renderer, TTF_Font* font, SDL_Surface* shotgun_surface) {
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