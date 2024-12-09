

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mutex>

#include "Game.h"
#include "StartMenue.h"







int main(int argc, char* argv[])
{
    using namespace cgame;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Fehler bei SDL_Init: %s", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        SDL_Log("Fehler bei TTF_Init: %s", SDL_GetError());
        return 1;
    }
    


    SDL_Window* window = SDL_CreateWindow(
        "CGame",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );


    if (!window) {
        SDL_Quit();
        return -1;
    }

    // Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    //game objects
    StartMenue menue(window, renderer);
    Game* game = nullptr;
    



    // main loop
    bool run = true;
    while (run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = false;
            }
            else if (event.type == SDL_KEYDOWN) { // Taste gedr�ckt
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    std::cout << "Escape-Taste gedr�ckt!" << std::endl;
                    run = false;
                    break;
                case SDLK_w:
                    break;
                case SDLK_a:
                    break;
                case SDLK_s:
                    break;
                case SDLK_d:
                    break;
                case SDLK_UP:
                    break;
                case SDLK_LEFT:
                    break;
                case SDLK_DOWN:
                    break;
                case SDLK_RIGHT:
                    break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                game = menue.startGameButton(mouseX, mouseY);
            }
            else if (event.type == SDL_KEYUP) { // Taste losgelassen
            }

        }


        // Inhalt anzeigen
        SDL_RenderPresent(renderer);
    }







    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}