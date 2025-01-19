#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;

bool is_running = false;
uint32_t* color_buffer = NULL; //a pointer to the first position of the array of colors

int window_width = 800;
int window_height = 600;

bool initialize_window(void)
{
   // configure a Window 
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
   {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
   };

   // Use SDL to query what is the fullscreen max. width and height
   SDL_DisplayMode display_mode;
   SDL_GetCurrentDisplayMode(0, &display_mode); 
   window_width = display_mode.w; 
   window_height = display_mode.h;

   // Create a SDL Window
   window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        SDL_WINDOW_BORDERLESS      
    );
    if (!window){
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }
    
    // Create a SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr, "Error creating SDL renderer.\n"); 
        return false;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    return true;
}

void setup()
{
   //  
   color_buffer = (uint32_t*)malloc(sizeof(uint32_t) * window_width * window_height);
   color_buffer_texture = SDL_CreateTexture(
    renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    window_width,
    window_height
    );
}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type)
    {
        case SDL_QUIT:
            is_running = false; 
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
    }
}

void update()
{
    //TODO:
}
void draw_grid()
{
    for(int y = 0; y < window_height; y+=10){
        for(int x = 0; x < window_width; x+=10){
            color_buffer[(window_width * y) + x] = 0xFF333333;
        }
    }
}

void render_color_buffer()
{
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(window_width * sizeof(uint32_t))        
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color)
{
    for(int y = 0; y < window_height; y++){
        for(int x = 0; x < window_width; x++){
            color_buffer[(window_width * y) + x] = color; 
        }
    }
}

void render()
{
    //TODO: 
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    draw_grid();

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

void destroy_window(void)
{
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(void) {
    /* TODO: Create a SDL Window */
    is_running = initialize_window();

    setup();

    while(is_running){
       process_input();
       update();
       render();  
    }

    destroy_window();

    return 0;
}
