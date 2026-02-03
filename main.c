#include <SDL.h>
#include <emscripten.h>
#include <stdlib.h>

// 1. Define our screen size
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

// 2. Global variables (The "State")
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// 3. This is your "Game Logic" function
// In Handmade Hero, this would be "GameUpdateAndRender"
void GameLoop() {
    // A. Input Handling (The "Message Loop")
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            // On web, we rarely "quit", but good practice
        }
    }

    // B. Render (Draw things)
    // Clear screen to Black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw a Red Rectangle (The "Hero")
    SDL_Rect fillRect = { SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25, 50, 50 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fillRect);

    // C. Present (Flip buffers)
    SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {
    // 4. Initialize SDL (The "Operating System" check)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return 1;
    }

    // 5. Create the Window and Renderer
    // This replaces "CreateWindowEx" from Win32
    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
    
    // 6. The Infinite Loop
    // On Windows: while(running) { ... }
    // On Web: We must delegate the loop to the browser:
    emscripten_set_main_loop(GameLoop, 0, 1);

    // 7. Cleanup (Rarely reached on web)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
