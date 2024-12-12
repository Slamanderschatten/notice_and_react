

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <mutex>
#include <thread>

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
    StartMenue* menue = new StartMenue(window, renderer);
    Game* game = nullptr;
    



    // main loop
    atomic<bool> run = true;
    while (run) {
        this_thread::sleep_for(chrono::milliseconds(10));
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game->stop();
                run = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (game) {
                    game->keyAction(event.key.keysym.sym);
                }
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    game->stop();
                    run = false;
                    break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (menue) {
                    game = menue->startGameButton(mouseX, mouseY);
                    if (game) {
                        game->start();
                        delete menue;
                        menue = nullptr;
                        SDL_RenderClear(renderer);
                    }
                }
            }
            else if (event.type == SDL_KEYUP) {
            }

        }


        // Inhalt anzeigen
        SDL_RenderPresent(renderer);
    }





    delete game;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}