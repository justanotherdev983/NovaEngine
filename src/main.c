#include "game.h"


int main() {
    game_state_t game = {0};
    
    if (!init_sdl(&game)) {
        printf("Failed to initialize SDL\n");
        cleanup(&game);
        return 1;
    }
    
    if (!load_resources(&game)) {
        printf("Failed to load resources\n");
        cleanup(&game);
        return 1;
    }

    init_game(&game);
    
    run_game(&game);
    debug_info(&game);
    cleanup(&game);
    
    return 0;
}