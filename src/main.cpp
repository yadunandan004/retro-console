#include <iostream>
#include <SDL.h>
#include "chip8.h"

// Constants for display scaling
const int SCALE = 10;           // Each Chip-8 pixel becomes 10x10 screen pixels
const int SCREEN_WIDTH = 64 * SCALE;   // 640 pixels
const int SCREEN_HEIGHT = 32 * SCALE;  // 320 pixels
const int TARGET_FRAME_TIME = 1000/60;

int main() {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL Init Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    // Create window with proper size and flags
    SDL_Window* window = SDL_CreateWindow(
        "Chip-8 Emulator",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cout << "Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create renderer with proper flags
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Create Chip-8 instance
    chip8 emulator;

    // Main game loop with proper event handling
    SDL_Event event;  // Actual object, not pointer
    bool running = true;
    emulator.loadRom("roms/ibm_logo.ch8");
    emulator.debugPrintMemory();
    while (running) {

        // Handle events
        auto start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {  // Pass address of event
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Clear screen with black color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        for (int i = 0; i < 20; i++) {
            emulator.cycle();
        }


        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        const uint8_t* dp = emulator.getDisplay();
        for (int y =0; y<32;y++) {
            for (int x=0; x<64; x++) {

                if (dp[ y * 64 +x] == 1) {
                    SDL_Rect rect = {x *SCALE,y*SCALE, SCALE,SCALE};
                    SDL_RenderFillRect(renderer,&rect);
                }
            }
        }
        auto end = SDL_GetTicks();
        if ((end-start) < TARGET_FRAME_TIME) {
            SDL_Delay(TARGET_FRAME_TIME- (end-start));
        }

        // Present the frame
        SDL_RenderPresent(renderer);
        emulator.updateTimers();
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}