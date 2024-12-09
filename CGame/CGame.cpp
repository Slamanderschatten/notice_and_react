

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
            else if (event.type == SDL_KEYDOWN) { // Taste gedrückt
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    std::cout << "Escape-Taste gedrückt!" << std::endl;
                    run = false;
                    break;
                case SDLK_a:
                    std::cout << "Taste 'A' gedrückt!" << std::endl;
                    break;
                case SDLK_UP:
                    std::cout << "Pfeil nach oben gedrückt!" << std::endl;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    game = menue.startGameButton(mouseX, mouseY);
                    break;
                default:
                    std::cout << "Andere Taste: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
                    break;
                }
            }
            else if (event.type == SDL_KEYUP) { // Taste losgelassen
                std::cout << "Taste losgelassen: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
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