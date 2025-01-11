#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void)
{
   /* TODO: configure a Window */ 
   if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
   {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
   };

   // TODO: Create a SDL Window
   window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_BORDERLESS      
    );
    if (!window){
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }

    // TODO: Create a SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        fprintf(stderr, "Error creating SDL renderer.\n"); 
        return false;
    }
    return true;
}

int main(void) {
    /* TODO: Create a SDL Window */
    is_running = initialize_window();
    return 0;
}
