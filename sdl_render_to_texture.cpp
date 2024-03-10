// @COMPILECMD g++ $@ $(pkg-config --libs SDL2_image SDL2_ttf) -ggdb
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Window dimensions
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG);

    SDL_Window* window = SDL_CreateWindow("Texture Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* texture1 = IMG_LoadTexture(windowRenderer, "dog.jpg");
    SDL_Texture* texture2 = IMG_LoadTexture(windowRenderer, "dog2.jpg");
    SDL_Texture* texture3 = SDL_CreateTexture(windowRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                                              WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_SetRenderTarget(windowRenderer, texture3);
    SDL_SetRenderDrawColor(windowRenderer, 0, 0, 0, 255);
    SDL_RenderClear(windowRenderer);
	//
	SDL_Rect r = {0, 0, 300, 300};
    SDL_RenderCopy(windowRenderer, texture1, nullptr, &r);
	r.x = 300;
    SDL_RenderCopy(windowRenderer, texture2, nullptr, &r);


    SDL_SetRenderTarget(windowRenderer, nullptr);
    SDL_SetRenderDrawColor(windowRenderer, 255, 255, 255, 255);
    SDL_RenderClear(windowRenderer);
    SDL_RenderCopy(windowRenderer, texture3, nullptr, nullptr);

    SDL_RenderPresent(windowRenderer);

    // Wait for user exit
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}
