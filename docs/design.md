# Design Doc

## Nova engine

Nova is a 3D doom-like game engine using ascii chars for rendering.

    // Enums

    typedef enum {
        NONE,
        QUIT,
        MOV_FORWARD,
        MOV_BACK,
        MOV_RIGHT,
        MOV_LEFT,
        MOUSE_LOOK,
    } input_type_e

    typedef enum {
        NONE,
        WALL,
        DOOR
    } tile_type_e

    typedef enum {
        ENGINE_OK,
        ENGINE_INIT_SDL_FAILED,
        ENGINE_INIT_WINDOW_FAILED,
        ENGINE_INIT_RENDERER_FAILED,
        ENGINE_INIT_FONT_FAILED,
        ENGINE_INIT_MAP_FAILED,

        ENGINE_RESOURCE_LOAD_FAILED,

        ENGINE_MEMORY_ALLOCATION_FAILED,

        ENGINE_WORLD_INVALID,
        ENGINE_PLAYER_INVALID,
        ENGINE_INPUT_INVALID,

        ENGINE_RENDER_SURFACE_CREATE_FAILED,
        ENGINE_RENDER_TEXTURE_CREATE_FAILED,

        ENGINE_COLLISION_DETECTION_FAILED,
    } error_type_e

    // Structs

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

    typedef struct {
        i32 screen_height;
        i32 screen_width;

        SDL_Font* font;
    } engine_config_t


    // Used for debugging
    typedef struct {
        
    } 2d_world_t

    typdef struct {
        
    } tile_editor_t

    typedef struct {
        map_t map;
        player_t player;
        camera_t camera;
        enemy_t enemy;
    } world_t

    typedef struct {
        SDL_Window* window;
        SDL_Renderer* renderer;
        // array of surfaces
        // array of textures
        
    } render_t

    typedef struct {
        input_type_e type;
    } input_handler_t

    typedef struct {
        render_t renderer;
        input_handler_t input_handler;
        world_t world;
        engine_config_t config;
        error_type_e cur_error_status;
    } engine_t

## Delirious adventure

### Description

Delirious adventure is FPS game using the Nova engine.

### API demo

    // Basic game

    int main() {
        engine_config_t config = {
            .screen_width = GAME_SCREEN_WIDTH,
            .screen_height = GAME_SCREEN_HEIGHT,
        }

        engine_t engine = engine_create(&config);
        engine_init(&engine);

        world_t* world = world_create();
        load_map(&world, "level1.neb"); // Using nebula formatting
        
        set_world(engine, world);

        while(!engine_quit(&engine)) {
            run(engine);
        }
        
        destroy(engine);
        
        return 0;
    }

## TODO: big

### Nebula tile editor

### Gravity physics system

## TODO: small
